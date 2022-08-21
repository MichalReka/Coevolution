#include "GeneticAlgorithm.h"
#include <future>
std::vector<Agent> GeneticAlgorithm::CreateNewGeneration(std::vector<Agent> population, std::vector<Agent> representatives)
{
	Agent eliteIndividual;
	eliteIndividualFitness = 0;
	tournamentSize = static_cast<int>(TOURNAMENT_SIZE_FACTOR * population.size());
	std::vector<int> fitnessList;

	//std::vector<std::future<float>> futures;
	//for (int i = 0; i < population.size(); i++) {
	//	Agent *agent = &population[i];
	//	futures.push_back(std::async([this, agent, representatives] {return this->Evaluate(*agent, representatives); }));
	//}

	//for (int i = 0; i < population.size(); i++) {
	//	float fitness = futures[i].get();
	//	fitnessList.push_back(fitness);
	//	if (fitness > eliteIndividualFitness) {
	//		eliteIndividualFitness = fitness;
	//		eliteIndividual = population[i];
	//		eliteIndividualIndex = i;
	//	}
	//}

	for (int i = 0; i < population.size(); i++) {
		int fitness = Evaluate(population[i], representatives);
		fitnessList.push_back(fitness);
		if (fitness > eliteIndividualFitness) {
			eliteIndividualFitness = fitness;
			eliteIndividual = population[i];
			eliteIndividualIndex = i;
		}
	}

	std::vector<Agent> newGeneration;
	newGeneration.push_back(eliteIndividual);
	int populationSize = population.size();
	while (newGeneration.size() != populationSize) {
		int firstParentIndex = SelectParentIndex(fitnessList, populationSize);
		int secondParentIndex = SelectParentIndex(fitnessList, populationSize);
		while (firstParentIndex == secondParentIndex) {
			secondParentIndex = SelectParentIndex(fitnessList, populationSize);
		}

		Agent child = Recombinate(population[firstParentIndex], population[secondParentIndex]);
		Mutate(child);
		newGeneration.push_back(child);
	}
	return newGeneration;
}

float GeneticAlgorithm::Evaluate(Agent& agent, std::vector<Agent> representatives) {
	Simulation simulation;
	representatives.push_back(agent);
	Actions g = static_cast<Actions>(representatives[0].responses[0][0][representatives[0].currentAction]);

	simulation.RunSimulation(representatives);
	simulation.CalculateFitness();
	float fitness = simulation.fitness;
	return fitness;
};

int GeneticAlgorithm::SelectParentIndex(std::vector<int> fitnessList, int populationSize) {
	int highestFitnessIndex = rand() % populationSize;
	for (int i = 0; i < tournamentSize; i++) {
		int fitnessIndexToCheck = rand() % populationSize;
		if (fitnessList[highestFitnessIndex] <= fitnessList[fitnessIndexToCheck]) {
			highestFitnessIndex = fitnessIndexToCheck;
		}
	}

	return highestFitnessIndex;
}

void GeneticAlgorithm::Mutate(Agent& agent) {
	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
			for (int actions = 0; actions < ACTIONS_MAX; actions++) {
				if (mutationRate > Utilities::GetRandomFloat()) {
					agent.responses[events][movements][actions] = rand() % ACTIONS_MAX;
				}
			}
		}
	}

	if (mutationRate > Utilities::GetRandomFloat()) {
		agent.agentTemplateSize = rand() % Environment::MAX_AGENTS_PER_TEMPLATE + 1;
	}
};

Agent GeneticAlgorithm::Recombinate(Agent& firstParent, Agent& secondParent) {
	Agent child;
	float firstParentBias = Utilities::GetRandomFloat();

	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
			for (int actions = 0; actions < ACTIONS_MAX; actions++) {
				if (firstParentBias > Utilities::GetRandomFloat()) {
					child.responses[events][movements][actions] = firstParent.responses[events][movements][actions];
				}
				else {
					child.responses[events][movements][actions] = secondParent.responses[events][movements][actions];
				}
			}
		}
	}
	child.agentTemplateSize = firstParent.agentTemplateSize;

	return child;
};