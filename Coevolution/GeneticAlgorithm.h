#pragma once
#include "Agent.h"
#include <vector>
#include "Utilities.h"

class GeneticAlgorithm
{
public:
	Agent eliteIndividual;
	int eliteIndividualFitness;
	float mutationRate = 0.05f;
	float const TOURNAMENT_SIZE_FACTOR = 0.05f;
	std::vector<Agent> CreateNewGeneration(std::vector<Agent> population, std::vector<Agent> representatives) {};
private:
	int tournamentSize = 0;
	int Evaluate(Agent agent, std::vector<Agent> representatives) {};
	void Mutate(Agent agent) {};
	Agent Recombinate(Agent firstParent, Agent secondParent) {};
	int SelectParentIndex(std::vector<int> fitnessList, int populationSize) {}
};

