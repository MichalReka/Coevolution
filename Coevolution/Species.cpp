#include "Species.h"

void Species::InitializeNewSpecies(bool initial) {
	population.clear();
	for (int i = 0; i < speciesSize; i++)
	{
		Agent individual;
		individual.InitializeRandomResponses();
		population.push_back(individual);
	}
	representativeIndex = rand() % speciesSize;
	if (initial) {
		population[representativeIndex].responses[ArrivedToEnergyBank][Waiting] = GoToProductSource;
		population[representativeIndex].responses[ArrivedToEnergyBank][GoingToProductSource] = GoToProductSource;
		population[representativeIndex].responses[ArrivedToProductSource][GoingToProductSource] = GoToProductDestination;
		population[representativeIndex].responses[ArrivedToProductSource][GoingToProductDestination] = GoToProductDestination;
	}
}

void Species::CreateNewGeneration(std::vector<Agent>& foreignRepresentatives) {
	population = geneticAlgorithm.CreateNewGeneration(population, foreignRepresentatives);
}

void Species::UpdateRepresentative() {
	representativeIndex = geneticAlgorithm.eliteIndividualIndex;
}


