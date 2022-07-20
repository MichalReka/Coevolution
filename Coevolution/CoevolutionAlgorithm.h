#pragma once
#include <vector>
#include "Species.h"
class CoevolutionAlgorithm
{
public:
	int currentFitness = 0;
	double fitnessChange = 0;
	int stagnateIterations = 0;
	int maxIterations = 100;
	std::vector<Species> allSpecies;
	std::vector<Species> bestSpeciesSet;
	void Run() {};
private:
	void InitializeFirstIteration() {};
};
