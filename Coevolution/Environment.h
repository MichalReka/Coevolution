#pragma once
#include <SFML/Graphics.hpp>

class Environment {
public:
	static sf::Vector2f SPAWN_POSITION;
	static sf::Vector2f ENERGY_REFILL_POSITION;
	static sf::Vector2f SIMULATION_GRAPH_SIZE;
	static sf::Vector2f PRODUCT_DROP_POSITION;
	static sf::Vector2f PRODUCT_TAKE_POSITION;
	static float MAX_PRODUCT_PER_AGENT;
	static float MAX_PRODUCT_ENERGY_MULTIPLIER;
	static float MAX_ENERGY_PER_AGENT;
};

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
	GoingToNearestProductRequester,
	GoingToNearestEnergyRequester,
	MOVEMENT_STATE_MAX
};

enum Actions
{
	GoToProductSource,
	GoToEnergyBank,
	GoToProductDestination,
	GoToNearestEnergyRequester,
	GoToNearestProductRequester,
	RequestEnergy,
	RequestProduct,
	//TakeAllPossibleProduct,
	//TakeEnoughProductToRefillEnergy,
	//TakeEnoughProductToDropIt,
	Continue,
	Wait,
	ACTIONS_MAX
};
