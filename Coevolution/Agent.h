#pragma once
#include "Environment.h";
#include <stdlib.h>

class Agent
{
public:
	int responses[EVENTS_MAX][MOVEMENT_STATE_MAX];
	void InitializeRandomResponses();
};