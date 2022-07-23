#pragma once
#include <vector>
#include "Species.h"
class CoevolutionAlgorithm
{
public:
	const float STAGNATE_FACTOR = 0.01;

	float currentFitness = 0;
	float fitnessChange = 0;
	int stagnateIterations = 0;

	int maxIterations = 1000;
	std::vector<Species> allSpecies;
	std::vector<Species> bestSpeciesSet;
	void Run() {};
private:
	void InitializeFirstIteration() {};
	void UpdateSpeciesRepresentatives() {};
	std::vector<Agent> GetRepresentativesForEvaluation(int indexToOmit) {};
};
