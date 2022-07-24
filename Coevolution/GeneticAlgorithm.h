#pragma once
#include "Agent.h"
#include "Utilities.h"
#include "Simulation.h"
#include <vector>

class GeneticAlgorithm
{
public:
	Agent eliteIndividual;
	int eliteIndividualFitness;
	float mutationRate = 0.05f;
	float const TOURNAMENT_SIZE_FACTOR = 0.01f;
	int const INDIVIDUALS_PER_SPECIES = 10000;
	std::vector<Agent> CreateNewGeneration(std::vector<Agent> population, std::vector<Agent> representatives);
private:
	int tournamentSize = 0;
	float Evaluate(Agent agent, std::vector<Agent> representatives);
	void Mutate(Agent agent);
	Agent Recombinate(Agent firstParent, Agent secondParent);
	int SelectParentIndex(std::vector<int> fitnessList, int populationSize);
};

