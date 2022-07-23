#include "CoevolutionAlgorithm.h"

void CoevolutionAlgorithm::Run() {
	this->InitializeFirstIteration();
	for (int i = 0; i < maxIterations; i++) {
		for (int i = 0; i < allSpecies.size(); i++) {
			allSpecies[i].CreateNewGeneration(GetRepresentativesForEvaluation(i));
		}

		UpdateSpeciesRepresentatives();
	}
}

void CoevolutionAlgorithm::InitializeFirstIteration() {
	Species species;
	species.InitializeNewSpecies();
	allSpecies.push_back(species);
}

std::vector<Agent> CoevolutionAlgorithm::GetRepresentativesForEvaluation(int indexToOmit) {
	std::vector<Agent> foreignRepresentatives;

	for (int i = 0; i < allSpecies.size(); i++) {
		if (i != indexToOmit) {
			foreignRepresentatives.push_back(allSpecies[i].representative);
		}
	}
	return foreignRepresentatives;
};

void CoevolutionAlgorithm::UpdateSpeciesRepresentatives() {
	for (Species species : allSpecies) {
		species.UpdateRepresentative();
	}
}