#include "Simulation.h"

void Simulation::RunSimulation(std::vector<Agent> agentTemplates) {
	////MOCK
	//MockSimulation(agentTemplates);
	////MOCK
	for (int i = 0; i < SIMULATION_MAX_ITERATIONS; i++)
	{
		for (Agent& agent : agentTemplates) {
			agent.DetectEvent();
		}

		for (Agent& agent : agentTemplates) {
			agent.PerformAction();
		}
	}

	for (Agent& agent : agentTemplates) {
		productsGatheredPerAgent = productsGatheredPerAgent + agent.totalProductGathered;
	}

	productsGatheredPerAgent = productsGatheredPerAgent / agentTemplates.size();
};

void Simulation::MockSimulation(std::vector<Agent> agentTemplates) {
	energySpentPerAgent = 1;
	productsGatheredPerAgent = 0;
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 7; j++)
		{
			int responseSum = 0;
			for (const Agent &agent : agentTemplates) {
				responseSum = agent.responses[i][j] + responseSum;
				productsGatheredPerAgent = (responseSum % 4 == 0) + productsGatheredPerAgent;
			}
		}
	}
	productsGatheredPerAgent = productsGatheredPerAgent / agentTemplates.size();
}

void Simulation::CalculateFitness() {
	fitness = productsGatheredPerAgent / energySpentPerAgent;
};