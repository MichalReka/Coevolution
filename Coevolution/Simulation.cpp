#include "Simulation.h"

void Simulation::RunSimulation(std::vector<Agent> agentTemplates) {
	////MOCK
	//MockSimulation(agentTemplates);
	////MOCK

	std::vector<Agent> realAgents;

	for (Agent& agentTemplate : agentTemplates) {
		for (int i = 0; i < agentTemplate.agentTemplateSize; i++) {
			Agent realAgent = agentTemplate;
			realAgents.push_back(realAgent);
		}
	}

	for (int i = 0; i < SIMULATION_MAX_ITERATIONS; i++)
	{
		for (Agent& agent : realAgents) {
			agent.DetectEvent(runtimeData.productRequesters, runtimeData.energyRequesters);
		}

		for (Agent& agent : realAgents) {
			agent.PerformAction(runtimeData.productRequesters, runtimeData.energyRequesters);
		}
	}

	for (Agent& agent : realAgents) {
		productsGatheredPerAgent = productsGatheredPerAgent + agent.totalProductGathered;
	}

	if (productsGatheredPerAgent > 0) {
		productsGatheredPerAgent = productsGatheredPerAgent / realAgents.size();
	}
}
std::thread Simulation::CreateSimulationThread(std::vector<Agent>& agentTemplates)
{
	return std::thread();
}
;

void Simulation::MockSimulation(std::vector<Agent> agentTemplates) {
	//energySpentPerAgent = 1;
	//productsGatheredPerAgent = 0;
	//for (int i = 0; i < 9; i++) {
	//	for (int j = 0; j < 7; j++)
	//	{
	//		int responseSum = 0;
	//		for (const Agent &agent : agentTemplates) {
	//			responseSum = agent.responses[i][j] + responseSum;
	//			productsGatheredPerAgent = (responseSum % 4 == 0) + productsGatheredPerAgent;
	//		}
	//	}
	//}
	//productsGatheredPerAgent = productsGatheredPerAgent / agentTemplates.size();
}

void Simulation::CalculateFitness() {
	fitness = productsGatheredPerAgent / energySpentPerAgent;
};