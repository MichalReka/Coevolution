#pragma once
#include "Agent.h"
#include "Utilities.h"
#include "Simulation.h"
#include <vector>
#include <ppl.h>

class GeneticAlgorithm
{
public:
	int eliteIndividualIndex;
	int eliteIndividualFitness;
	float mutationRate = 0.1f;
	float const TOURNAMENT_SIZE_FACTOR = 0.1f;
	std::vector<Agent> CreateNewGeneration(std::vector<Agent> population, std::vector<Agent> representatives);

	GeneticAlgorithm() = default;
	GeneticAlgorithm(GeneticAlgorithm const&) = default;
	// user-defined copy assignment (copy-and-swap idiom)
	GeneticAlgorithm& operator=(GeneticAlgorithm other)
	{
		std::swap(eliteIndividualIndex, other.eliteIndividualIndex);
		std::swap(eliteIndividualFitness, other.eliteIndividualFitness);
		return *this;
	}
private:
	int tournamentSize = 0;
	float Evaluate(Agent& agent, std::vector<Agent> representatives);
	void Mutate(Agent& agent);
	Agent Recombinate(Agent& firstParent, Agent& secondParent);
	int SelectParentIndex(std::vector<int> fitnessList, int populationSize);
};

