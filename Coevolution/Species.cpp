#include "Species.h"

void Species::InitializeNewSpecies() {
	population.clear();
	for (int i = 0; i < speciesSize; i++)
	{
		Agent individual;
		individual.InitializeRandomResponses();
		population.push_back(individual);
	}
	representative = population[rand() % speciesSize];
}

