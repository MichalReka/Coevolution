#include<vector>
#include "Agent.h"

#pragma once
class Simulation
{
public:
	const int AGENTS_PER_TEMPLATE = 10;
	const int SIMULATION_MAX_ITERATIONS = 2000;
	float productsGatheredPerAgent = 0;
	float energySpentPerAgent = 0;
	float fitness = 0;

	void RunSimulation(std::vector<Agent> agentTemplates);
	void MockSimulation(std::vector<Agent> agentTemplates);
	void CalculateFitness();
};

