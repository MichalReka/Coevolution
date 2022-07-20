#include "Agent.h"
void Agent::InitializeRandomResponses() {
	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
			responses[events][movements] = rand() % ACTIONS_MAX;
		}
	}
}