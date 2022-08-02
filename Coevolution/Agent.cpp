#include "Agent.h"

void Agent::InitializeRandomResponses() {
	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
			responses[events][movements] = rand() % ACTIONS_MAX;
		}
	}
}

void Agent::MoveTo(sf::Vector2f destination)
{
	sf::Vector2f offset = destination - position;
	Utilities::NormalizeVector(offset);
	if (currentEnergy <= 0) {
		offset = sf::Vector2f(offset.x / 5, offset.y / 5);
	}
	else {
		float energyMultiplier = Utilities::ConvertRange(0, Environment::MAX_PRODUCT_PER_AGENT, 1, Environment::MAX_PRODUCT_ENERGY_MULTIPLIER, currentProduct);
		currentEnergy = currentEnergy - 1 * energyMultiplier;
	}
	position = position + offset;
}

void Agent::MoveAccordingToState()
{
	switch (movementState) {
	case GoingToProductSource:
		MoveTo(Environment::PRODUCT_TAKE_POSITION);
		break;
	case GoingToEnergyBank:
		MoveTo(Environment::ENERGY_REFILL_POSITION);
		break;
	case GoingToProductDestination:
		MoveTo(Environment::PRODUCT_DROP_POSITION);
	}
}

//GotEnergy,
//GotProduct,

void Agent::DetectEvent()
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
	else if (Utilities::IsNear(position, Environment::PRODUCT_TAKE_POSITION) && movementState == GoingToProductSource) {
		lastEvent = ArrivedToProductSource;
		currentProduct = Environment::MAX_PRODUCT_PER_AGENT;
	}
	else if (!Utilities::IsNear(position, Environment::ENERGY_REFILL_POSITION)) {

	}
}
void Agent::PerformAction()
{
	Actions actionToPerform = static_cast<Actions>(responses[lastEvent][movementState]);

	if (actionToPerform == Continue) {
		return;
	}

	switch (actionToPerform) { //TYLKO USTAWIENIE STANU, POTEM
	case GoToProductSource:
		movementState = GoingToProductSource;
		break;
	case GoToEnergyBank:
		movementState = GoingToEnergyBank;
		break;
	case GoToProductDestination:
		movementState = GoingToProductDestination;
		break;
	case GoToNearestEnergyRequester:
		movementState = GoingToNearestEnergyRequester;
		break;
	case GoToNearestProductRequester:
		movementState = GoingToNearestProductRequester;
		break;
	case RequestEnergy:
		break;
	case RequestProduct:
		break;
	//case TakeAllPossibleProduct:
	//	if (Utilities::IsNear(position, Environment::PRODUCT_TAKE_POSITION)) {
	//		currentProduct = Environment::MAX_PRODUCT_PER_AGENT;
	//	}
	//	break;
	//case TakeEnoughProductToRefillEnergy:
	//	break;
	//case TakeEnoughProductToDropIt:
	//	break;
	case Wait:
		break;
	}

	MoveAccordingToState();
}