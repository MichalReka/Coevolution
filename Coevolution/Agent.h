#pragma once
#include "Environment.h";
#include <stdlib.h>

class Agent
{
public:

	int responses[EVENTS_MAX][MOVEMENT_STATE_MAX];
	float currentEnergy = 200;

	void InitializeRandomResponses();
	void DetectEvent();
	void PerformAction();

private:
	Actions currentAction = Wait;
	Events lastEvent = ArrivedToEnergyBank;
};