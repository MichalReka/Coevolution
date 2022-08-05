#pragma once
#include "Environment.h";
#include <stdlib.h>
#include "Utilities.h"

class Agent
{
public:
	sf::Vector2f position = sf::Vector2f(1, 1);

	int responses[EVENTS_MAX][MOVEMENT_STATE_MAX];
	int agentTemplateSize = 1;

	float currentEnergy = Environment::MAX_ENERGY_PER_AGENT;
	float currentProduct = 0;

	float totalEnergySpent = 0;
	float totalProductGathered = 0;
	bool requestingProduct = false;
	bool requestingEnergy = false;

	void InitializeRandomResponses();
	void DetectEvent(std::map<Agent*, Agent>& productRequesters,
		std::map<Agent*, Agent>& energyRequesters);
	void PerformAction(std::map<Agent*, Agent>& productRequesters,
		std::map<Agent*, Agent>& energyRequesters);

private:
	Actions currentAction = Wait;
	Events lastEvent = ArrivedToEnergyBank;
	MovementState movementState = Waiting;

	void MoveAccordingToState();
	void MoveTo(sf::Vector2f destination);
	void HandleGoingToRequesters(std::map<Agent*, Agent>& requesters);
	bool TransferToNearbyProductRequester(std::map<Agent*, Agent>& productRequesters);
	bool TransferToNearbyEnergyRequester(std::map<Agent*, Agent>& energyRequesters);
};