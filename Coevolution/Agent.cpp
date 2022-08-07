#include "Agent.h"

void Agent::InitializeRandomResponses() {
	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
			for (int actions = 0; actions < ACTIONS_MAX; actions++) {
				responses[events][movements][actions] = rand() % ACTIONS_MAX;
			}
		}
	}
	agentTemplateSize = rand() % Environment::MAX_AGENTS_PER_TEMPLATE + 1;
}

void Agent::MoveTo(sf::Vector2f destination)
{
	sf::Vector2f offset = destination - position;
	Utilities::NormalizeVector(offset);
	if (currentEnergy <= 0) {
		offset = sf::Vector2f(offset.x / Environment::ZERO_ENERGY_SLOWUP, offset.y / Environment::ZERO_ENERGY_SLOWUP);
		if (currentProduct > 0) {
			offset = sf::Vector2f(offset.x / 2, offset.y / 2);
		}
	}
	else {
		float energyMultiplier = Utilities::ConvertRange(0, Environment::MAX_PRODUCT_PER_AGENT, 1, Environment::MAX_PRODUCT_ENERGY_SLOWUP, currentProduct);
		if (energyMultiplier > 1) {
			auto x = 10;
		}
		currentEnergy = currentEnergy - 1 * energyMultiplier;
	}
	position = position + offset;
}

void Agent::HandleGoingToRequesters(std::map<Agent*, Agent>& requesters)
{
	if (requesters.size() == 0 || (requesters.size() == 1 && requesters.count(this) == 1)) {
		movementState = Waiting;
		return;
	}

	double minDistance = 99999;
	sf::Vector2f direction;

	for (auto& requester : requesters)
	{
		if (requester.first != this) {
			double distance = Utilities::GetVectorLength(requester.second.position.x, requester.second.position.y);
			if (distance < minDistance) {
				minDistance = distance;
				direction = requester.second.position;
			}
		}
	}

	MoveTo(direction);
}

bool Agent::TransferToNearbyProductRequester(std::map<Agent*, Agent>& productRequesters)
{
	Agent* candidate = NULL;
	for (auto& requester : productRequesters)
	{
		if (this != requester.first && Utilities::IsNear(position, requester.second.position)) {
			requester.first->currentProduct = requester.first->currentProduct + currentProduct;
			currentProduct = 0;
			candidate = requester.first;
			break;
		}
	}

	if (candidate == NULL) {
		return false;
	}

	candidate->lastEvent = GotProduct;
	productRequesters.erase(candidate);
	return true;
}

bool Agent::TransferToNearbyEnergyRequester(std::map<Agent*, Agent>& energyRequesters)
{
	Agent* candidate = NULL;
	for (auto& requester : energyRequesters)
	{
		if (this != requester.first && Utilities::IsNear(position, requester.second.position)) {
			requester.first->currentEnergy = requester.first->currentEnergy + currentEnergy;
			currentEnergy = 0;
			if (requester.first->currentEnergy > Environment::MAX_ENERGY_PER_AGENT) {
				float overflow = requester.first->currentEnergy - Environment::MAX_ENERGY_PER_AGENT;
				currentEnergy = overflow;
				requester.first->currentEnergy = requester.first->currentEnergy - overflow;
			}
			candidate = requester.first;
			break;
		}
	}

	if (candidate == NULL) {
		return false;
	}

	candidate->lastEvent = GotEnergy;
	energyRequesters.erase(candidate);
	return true;
}

void Agent::MoveAccordingToState()
{
	switch (movementState) {
	case GoingToProductSourceToTakeMax:
		MoveTo(Environment::PRODUCT_TAKE_POSITION);
		break;
	case GoingToProductSourceToTakeHalf:
		MoveTo(Environment::PRODUCT_TAKE_POSITION);
		break;
	case GoingToProductSourceToTakeQuater:
		MoveTo(Environment::PRODUCT_TAKE_POSITION);
		break;
	case GoingToEnergyBank:
		MoveTo(Environment::ENERGY_REFILL_POSITION);
		break;
	case GoingToProductDestination:
		MoveTo(Environment::PRODUCT_DROP_POSITION);
	case GoingToNearestEnergyRequester:
		break;
	case GoingToNearestProductRequester:
		MoveTo(Environment::PRODUCT_DROP_POSITION);
		break;
	}
}

void Agent::DetectEvent(std::map<Agent*, Agent>& productRequesters,
	std::map<Agent*, Agent>& energyRequesters)
{
	if (currentEnergy <= 0 && lastEvent != LackOfEnergy) {
		lastEvent = LackOfEnergy;
	}
	//else if (currentAction == TransferProduct) {
	//	lastEvent = TransferedProduct;
	//}
	//else if (currentAction == TransferSpareEnergy) {
	//	lastEvent = TransferedEnergy;
	//}
	else if (Utilities::IsNear(position, Environment::ENERGY_REFILL_POSITION)) {
		lastEvent = ArrivedToEnergyBank;
		currentEnergy = Environment::MAX_ENERGY_PER_AGENT;
	}
	else if (Utilities::IsNear(position, Environment::PRODUCT_DROP_POSITION)) {
		lastEvent = ArrivedToProductDestination;
		totalProductGathered = totalProductGathered + currentProduct;
		currentProduct = 0;
	}
	else if (Utilities::IsNear(position, Environment::PRODUCT_TAKE_POSITION) 
		&& (movementState == GoingToProductSourceToTakeHalf 
			|| movementState == GoingToProductSourceToTakeMax 
			|| movementState == GoingToProductSourceToTakeQuater)) {
		lastEvent = ArrivedToProductSource;
		if (movementState == GoingToProductSourceToTakeMax) {
			currentProduct = Environment::MAX_PRODUCT_PER_AGENT;
		}
		else if (movementState == GoingToProductSourceToTakeHalf) {
			currentProduct = Environment::MAX_PRODUCT_PER_AGENT / 2;
		}
		else if (movementState == GoingToProductSourceToTakeQuater) {
			currentProduct = Environment::MAX_PRODUCT_PER_AGENT / 4;
		}
	}
	else if (requestingEnergy && energyRequesters.count(this) == 0) {
		lastEvent = GotEnergy;
			requestingEnergy = false;
	}
	else if (requestingProduct && productRequesters.count(this) == 0) {
		lastEvent = GotProduct;
			requestingProduct = false;
	}
	else if (movementState == GoingToNearestEnergyRequester && TransferToNearbyEnergyRequester(energyRequesters)) {
		lastEvent = TransferedEnergy;
	}
	else if (movementState == GoingToNearestProductRequester && TransferToNearbyProductRequester(productRequesters)) {
		lastEvent = TransferedProduct;
	}
}
void Agent::PerformAction(std::map<Agent*, Agent>& productRequesters,
	std::map<Agent*, Agent>& energyRequesters)
{
	Actions lastAction = this->currentAction;
	this->currentAction = static_cast<Actions>(responses[lastEvent][movementState][lastAction]);

	if (currentAction == Continue) {
		return;
	}

	switch (currentAction) { //TYLKO USTAWIENIE STANU, POTEM
	case GoToProductSourceToTakeQuater:
		movementState = GoingToProductSourceToTakeQuater;
		break;
	case GoToProductSourceToTakeHalf:
		movementState = GoingToProductSourceToTakeHalf;
		break;
	case GoToProductSourceToTakeMax:
		movementState = GoingToProductSourceToTakeMax;
		break;
	case GoToEnergyBank:
		movementState = GoingToEnergyBank;
		break;
	case GoToProductDestination:
		movementState = GoingToProductDestination;
		break;
	case GoToNearestEnergyRequester:
		movementState = GoingToNearestEnergyRequester;
		HandleGoingToRequesters(energyRequesters);
		break;
	case GoToNearestProductRequester:
		movementState = GoingToNearestProductRequester;
		HandleGoingToRequesters(productRequesters);
		break;
	case RequestEnergy:
		requestingEnergy = true;
		energyRequesters[this];
		break;
	case RequestProduct:
		requestingProduct = true;
		productRequesters[this];
		break;
	case Wait:
		movementState = Waiting;
		break;
	}

	MoveAccordingToState();
}