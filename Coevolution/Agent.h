#pragma once
#include "Environment.h";
#include <stdlib.h>
#include "Utilities.h"
#include <iostream>
#include <set>

class Agent
{
public:
	sf::Vector2f position = sf::Vector2f(1, 1);

	int responses[EVENTS_MAX][MOVEMENT_STATE_MAX][ACTIONS_MAX];
	int agentTemplateSize = 1;

	float currentEnergy = Environment::MAX_ENERGY_PER_AGENT;
	float currentProduct = 0;

	float energyTransfered = 0;
	float productTransfered = 0;

	float totalEnergySpent = 0;
	float totalProductGathered = 0;
	bool requestingProduct = false;
	bool requestingEnergy = false;

	void InitializeRandomResponses();
	void DetectEvent(std::set<Agent*>& productRequesters,
		std::set<Agent*>& energyRequesters);
	void PerformAction(std::set<Agent*>& productRequesters,
		std::set<Agent*>& energyRequesters);
	Actions currentAction = Wait;
private:
	Events lastEvent = ArrivedToEnergyBank;
	MovementState movementState = Waiting;

	void MoveAccordingToState();
	void MoveTo(sf::Vector2f destination);
	void HandleGoingToRequesters(std::set<Agent*>& requesters);
	bool TransferToNearbyProductRequester(std::set<Agent*>& productRequesters);
	bool TransferToNearbyEnergyRequester(std::set<Agent*>& energyRequesters);
};