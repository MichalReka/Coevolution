#pragma once
enum Events
{
	LackOfEnergy,
	ArrivedToEnergyBank,
	ArrivedToProductSource,
	ArrivedToProductDestination,
	CollidedWithOther,
	TransferedEnergy,
	TransferedProduct,
	GotEnergy,
	GotProduct,
	EVENTS_MAX
};

enum MovementState {
	Waiting,
	GoingToProductSource,
	GoingToEnergyBank,
	GoingToProductDestination,
	GoingToNearestIndividual,
	GoingToProductRequester,
	GoingToEnergyRequester,
	MOVEMENT_STATE_MAX
};

enum Actions
{
	GoToProductSource,
	GoToEnergyBank,
	GoToProductDestination,
	GoToNearestIndividual,
	GoToEnergyRequester,
	GoToProductRequester,
	RequestEnergy,
	RequestProduct,
	TransferAllEnergy,
	Transfer,
	TransferProduct,
	TakeAllPossibleProduct,
	TakeEnoughProductToRefillEnergy,
	TakeEnoughProductToDropIt,
	Continue,
	Wait,
	ACTIONS_MAX
};
