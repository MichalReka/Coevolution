#include<vector>
#include "Agent.h"

#pragma once
class Simulation
{
public:
	const int AGENTS_PER_TEMPLATE = 10;
	float productsGatheredPerAgent = 0;
	float energySpentPerAgent = 0;
	float fitness = 0;

	void RunSimulation(std::vector<Agent> agentTemplates) {};
private:
	void CalculateFitness() {};
};

