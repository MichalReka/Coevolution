#include "GeneticAlgorithm.h"
std::vector<Agent> GeneticAlgorithm::CreateNewGeneration(std::vector<Agent> population, std::vector<Agent> representatives)
{
	eliteIndividualFitness = 0;
	tournamentSize = static_cast<int>(TOURNAMENT_SIZE_FACTOR * population.size());
	std::vector<int> fitnessList;
	for (Agent individual : population) {
		int fitness = Evaluate(individual, representatives);
		fitnessList.push_back(fitness);
		if (fitness > eliteIndividualFitness) {
			fitness = eliteIndividualFitness;
			eliteIndividual = individual;
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
}

int GeneticAlgorithm::Evaluate(Agent agent, std::vector<Agent> representatives) {};

int GeneticAlgorithm::SelectParentIndex(std::vector<int> fitnessList, int populationSize) {
	std::vector<int> fitnessIndexesTournament;
	int highestFitnessIndex = 0;
	for (int i = 0; i < tournamentSize; i++) {
		int fitnessIndexToCheck = rand() % populationSize;
		if (fitnessList[highestFitnessIndex] < fitnessList[fitnessIndexToCheck]) {
			highestFitnessIndex = fitnessIndexToCheck;
		}
	}

	return highestFitnessIndex;
}

void GeneticAlgorithm::Mutate(Agent agent) {
	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
			if (mutationRate > Utilities::GetRandomFloat()) {
				agent.responses[events][movements] = rand() % ACTIONS_MAX;
			}
		}
	}
};

Agent Recombinate(Agent firstParent, Agent secondParent) {
	Agent child;
	float firstParentBias = Utilities::GetRandomFloat();

	for (int events = 0; events < EVENTS_MAX; events++)
	{
		for (int movements = 0; movements < MOVEMENT_STATE_MAX; movements++) {
			if (firstParentBias > Utilities::GetRandomFloat()) {
				child.responses[events][movements] = firstParent.responses[events][movements];
			}
			else {
				child.responses[events][movements] = secondParent.responses[events][movements];
			}
		}
	}

	return child;
};