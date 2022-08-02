#pragma once
#include "Environment.h";
#include <stdlib.h>
#include "Utilities.h"

class Agent
{
public:
	sf::Vector2f position = sf::Vector2f(1, 1);

	int responses[EVENTS_MAX][MOVEMENT_STATE_MAX];
	float currentEnergy = Environment::MAX_ENERGY_PER_AGENT;
	float currentProduct = 0;

	float totalEnergySpent = 0;
	float totalProductGathered = 0;

	void InitializeRandomResponses();
	void DetectEvent();
	void PerformAction();

private:
	Actions currentAction = Wait;
	Events lastEvent = ArrivedToEnergyBank;
	MovementState movementState = Waiting;

	void MoveAccordingToState();
	void MoveTo(sf::Vector2f destination);
};