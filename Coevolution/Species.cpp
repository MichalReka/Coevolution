#include "Species.h"

void Species::InitializeNewSpecies() {
	for (int i = 0; i < speciesSize; i++)
	{
		Agent individual;
		individual.InitializeRandomResponses();
		population.push_back(individual);
	}
	representativeIndex = rand() % speciesSize;
}

void Species::CreateNewGeneration(std::vector<Agent>& foreignRepresentatives) {
	population = geneticAlgorithm.CreateNewGeneration(population, foreignRepresentatives);
}

void Species::UpdateRepresentative() {
	representativeIndex = geneticAlgorithm.eliteIndividualIndex;
}


