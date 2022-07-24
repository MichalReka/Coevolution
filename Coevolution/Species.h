#pragma once
#include "GeneticAlgorithm.h"
class Species
{
public:
	std::vector<Agent> population;
	Agent representative;
	int speciesSize = 100;

	void InitializeNewSpecies();
	void CreateNewGeneration(std::vector<Agent> foreignRepresentatives);
	void UpdateRepresentative();
private:
	GeneticAlgorithm geneticAlgorithm;
};

