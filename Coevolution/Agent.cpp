#include "Agent.h"

void Agent::InitializeRandomResponses() {
	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
				for (int energyState = 0; energyState < AGENT_ENERGY_STATE_MAX; energyState++) {
					for (int productState = 0; productState < AGENT_PRODUCT_STATE_MAX; productState++) {
						responses[events][movements][energyState][productState] = rand() % ACTIONS_MAX;
					}
				}
		}
	}
	agentTemplateSize = rand() % Environment::MAX_AGENTS_PER_TEMPLATE + 1;
}

void Agent::MoveTo(sf::Vector2f destination)
{
	if (destination == position) {
		return;
	}
	sf::Vector2f offset = destination - position;
	Utilities::NormalizeVector(offset);
	if (currentEnergy <= 0) {
		offset = sf::Vector2f(offset.x / Environment::ZERO_ENERGY_SLOWUP, offset.y / Environment::ZERO_ENERGY_SLOWUP);
		if (currentProduct > 0) {
			offset = sf::Vector2f(offset.x / Environment::MAX_PRODUCT_SLOWUP, offset.y / Environment::MAX_PRODUCT_SLOWUP);
		}
	}
	else {
		float energyMultiplier = Utilities::ConvertRange(0, Environment::MAX_PRODUCT_PER_AGENT, 1, Environment::MAX_PRODUCT_ENERGY_SLOWUP, currentProduct);

		currentEnergy = currentEnergy - 1 * energyMultiplier;
		if (currentEnergy < 0) {
			currentEnergy = 0;
		}
	}
	position = position + offset;
}

void Agent::HandleGoingToRequesters(std::set<Agent*>& requesters)
{
	if (requesters.size() == 0 || (requesters.size() == 1 && requesters.count(this) == 1)) {
		movementState = Waiting;
		return;
	}

	double minDistance = 99999;
	sf::Vector2f direction;

	for (auto& requester : requesters)
	{
		if (requester != this) {
			sf::Vector2f v(requester->position.x - this->position.x, requester->position.y - this->position.y);
			double distance = Utilities::GetVectorLength(v.x, v.y);
			if (distance < minDistance && distance > 0) {
				minDistance = distance;
				direction = requester->position;
			}
		}
	}

	if (direction.x == 0) {
		movementState = Waiting;
		return;
	}

	MoveTo(direction);
}

bool Agent::TransferToNearbyProductRequester(std::set<Agent*>& productRequesters)
{
	Agent* candidate = NULL;
	for (auto& requester : productRequesters)
	{
		if (this != requester && Utilities::IsNear(position, requester->position, 2)) {
			float transfered = currentProduct;

			requester->currentProduct = requester->currentProduct + currentProduct;
			currentProduct = 0;
			if (requester->currentProduct > Environment::MAX_PRODUCT_PER_AGENT) {
				float overflow = requester->currentProduct - Environment::MAX_PRODUCT_PER_AGENT;
				currentProduct = overflow;
				requester->currentProduct = requester->currentProduct - overflow;
				transfered = transfered - overflow;
			}
			productTransfered = productTransfered + transfered;
			candidate = requester;
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

bool Agent::TransferToNearbyEnergyRequester(std::set<Agent*>& energyRequesters)
{
	Agent* candidate = NULL;
	for (auto& requester : energyRequesters)
	{
		if (this != requester && Utilities::IsNear(position, requester->position, 2)) {
			float transfered = currentEnergy;

			requester->currentEnergy = requester->currentEnergy + currentEnergy;
			currentEnergy = 0;
			if (requester->currentEnergy > Environment::MAX_ENERGY_PER_AGENT) {
				float overflow = requester->currentEnergy - Environment::MAX_ENERGY_PER_AGENT;
				currentEnergy = overflow;
				requester->currentEnergy = requester->currentEnergy - overflow;
				transfered = transfered - overflow;

			}
			energyTransfered = energyTransfered + transfered;
			candidate = requester;
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
	//case GoingToProductSourceToTakeHalf:
	//	MoveTo(Environment::PRODUCT_TAKE_POSITION);
	//	break;
	//case GoingToProductSourceToTakeQuater:
	//	MoveTo(Environment::PRODUCT_TAKE_POSITION);
	//	break;
	case GoingToEnergyBank:
		MoveTo(Environment::ENERGY_REFILL_POSITION);
		break;
	case GoingToProductDestination:
		MoveTo(Environment::PRODUCT_DROP_POSITION);
	}
}

void Agent::DetectEvent(std::set<Agent*>& productRequesters,
	std::set<Agent*>& energyRequesters)
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
	//else if (Utilities::IsNear(position, Environment::PRODUCT_TAKE_POSITION) 
	//	&& (movementState == GoingToProductSourceToTakeHalf 
	//		|| movementState == GoingToProductSourceToTakeMax 
	//		|| movementState == GoingToProductSourceToTakeQuater)) {
	else if (Utilities::IsNear(position, Environment::PRODUCT_TAKE_POSITION)
		&& movementState == GoingToProductSourceToTakeMax) {
		lastEvent = ArrivedToProductSource;
		if (movementState == GoingToProductSourceToTakeMax) {
			currentProduct = Environment::MAX_PRODUCT_PER_AGENT;
		}
		//else if (movementState == GoingToProductSourceToTakeHalf) {
		//	currentProduct = Environment::MAX_PRODUCT_PER_AGENT / 2;
		//}
		//else if (movementState == GoingToProductSourceToTakeQuater) {
		//	currentProduct = Environment::MAX_PRODUCT_PER_AGENT / 4;
		//}
	}
	else if (movementState == GoingToNearestEnergyRequester && TransferToNearbyEnergyRequester(energyRequesters)) {
		lastEvent = TransferedEnergy;
	}
	else if (movementState == GoingToNearestProductRequester && TransferToNearbyProductRequester(productRequesters)) {
		lastEvent = TransferedProduct;
	}
}
void Agent::PerformAction(std::set<Agent*>& productRequesters,
	std::set<Agent*>& energyRequesters)
{
	Actions lastAction = this->currentAction;
	if (lastAction < 0) {
		return;
	}

	int energyState = currentEnergy == 0 ? NoEnergy : HaveEnergy;
	int productState = currentProduct == 0 ? NoProduct : HaveProduct;
	this->currentAction = static_cast<Actions>(responses[lastEvent][movementState][energyState][productState]);

	if (currentAction == Continue) {
		return;
	}

	switch (currentAction) { //TYLKO USTAWIENIE STANU, POTEM
	//case GoToProductSourceToTakeQuater:
	//	movementState = GoingToProductSourceToTakeQuater;
	//	break;
	//case GoToProductSourceToTakeHalf:
	//	movementState = GoingToProductSourceToTakeHalf;
	//	break;
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
		energyRequesters.insert(this);
		break;
	case RequestProduct:
		productRequesters.insert(this);
		break;
	case Wait:
		movementState = Waiting;
		break;
	}

	MoveAccordingToState();
}