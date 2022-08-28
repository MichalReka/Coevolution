#include <vector>
#include <map>
#include "Agent.h"
#include <SFML/Graphics.hpp>
#include <thread>
#pragma once
struct SimulationRuntimeData {
public:
	std::set<Agent*> productRequesters;
	std::set<Agent*> energyRequesters;
};

#pragma once
class Simulation
{
public:
	const int AGENTS_PER_TEMPLATE = 1;
	const int SIMULATION_MAX_ITERATIONS = 350;

	float fitness = 0;
	float productsGatheredPerAgent = 0;
	float energySpentPerAgent = 1;
	float productTransferedPerAgent = 0;
	float energyTransferedPerAgent = 0;
	SimulationRuntimeData runtimeData;

	void RunSimulation(std::vector<Agent>& agentTemplates);
	std::thread CreateSimulationThread(std::vector<Agent>& agentTemplates);
	void MockSimulation(std::vector<Agent> agentTemplates);
	void CalculateFitness();
};

