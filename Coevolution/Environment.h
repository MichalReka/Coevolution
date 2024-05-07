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
	static float MAX_PRODUCT_ENERGY_SLOWUP;
	static float MAX_PRODUCT_SLOWUP;
	static float ZERO_ENERGY_SLOWUP;
	static float MAX_ENERGY_PER_AGENT;
	static float AGENT_SPEED;
	static int MAX_AGENTS_PER_TEMPLATE;
};

enum Events
{
	LackOfEnergy,
	ArrivedToEnergyBank,
	ArrivedToProductSource,
	ArrivedToProductDestination,
	TransferedEnergy,
	//TransferedProduct,
	GotEnergy,
	GotProduct,
	EVENTS_MAX
};

enum MovementState {
	Waiting,
	GoingToProductSourceToTakeMax,
	GoingToProductSourceToTakeNothing,
	//GoingToProductSourceToTakeQuater,
	GoingToEnergyBank,
	GoingToProductDestination,
	GoingToNearestIndividual,
	//GoingToNearestProductRequester,
	GoingToNearestEnergyRequester,
	MOVEMENT_STATE_MAX
};

enum Actions
{
	GoToProductSourceToTakeMax,
	GoToProductSourceToTakeNothing,
	//GoToProductSourceToTakeQuater,
	GoToEnergyBank,
	GoToProductDestination,
	GoToNearestEnergyRequester,
	//GoToNearestProductRequester,
	RequestEnergy,
	//RequestProduct,
	//Continue,
	Wait,
	ACTIONS_MAX = 11
};

enum AgentEnergyState {
	NoEnergy,
	HaveEnergy,
	AGENT_ENERGY_STATE_MAX
};

enum AgentProductState {
	NoProduct,
	HaveProduct,
	AGENT_PRODUCT_STATE_MAX
};