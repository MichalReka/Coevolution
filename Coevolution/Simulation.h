#include<vector>
#include "Agent.h"
#include <SFML/Graphics.hpp>

#pragma once
class Simulation
{
public:
	const int AGENTS_PER_TEMPLATE = 1;
	const int SIMULATION_MAX_ITERATIONS = 2000;

	float productsGatheredPerAgent = 0;
	float energySpentPerAgent = 1;
	float fitness = 0;

	void RunSimulation(std::vector<Agent> agentTemplates);
	void MockSimulation(std::vector<Agent> agentTemplates);
	void CalculateFitness();
};

struct SimulationRuntimeData {
public:
	std::vector<Agent> productRequesters;
	std::vector<Agent> energyRequesters;
};

