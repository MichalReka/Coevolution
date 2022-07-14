#pragma once
#include "GeneticAlgorithm.h"
class Species
{
public:
	GeneticAlgorithm geneticAlgorithm;
	std::vector<Agent> population;
	std::vector<Agent> foreignRepresentatives;
	Agent representative;

	void InitializeNewSpecies() {};
};

