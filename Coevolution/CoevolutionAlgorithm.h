#pragma once
#include <vector>
#include <iostream>
#include "Species.h"
class CoevolutionAlgorithm
{
	//TODO: ARCHIWUM, MECHANIZM WYKRYWANIA STAGNACJI I DODAWANIA/USUWANIA GATUNKÓW!
public:
	const float STAGNATE_FACTOR = 0.01;

	float currentFitness = 0;
	float previousFitness = 0;
	float fitnessChange = 0;
	int stagnateIterations = 0;

	int maxIterations = 1000;
	std::vector<Species> allSpecies;
	std::vector<Species> bestSpeciesSet;
	void Run();
private:
	void InitializeFirstIteration();
	void UpdateCurrentFitness();
	void UpdateSpeciesRepresentatives();
	std::vector<Agent> GetRepresentativesForEvaluation(int indexToOmit);
};
