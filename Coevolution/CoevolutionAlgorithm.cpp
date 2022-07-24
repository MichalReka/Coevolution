#include "CoevolutionAlgorithm.h"

void CoevolutionAlgorithm::Run() {
	this->InitializeFirstIteration();
	this->InitializeFirstIteration(); //MOCK
	for (int i = 0; i < maxIterations; i++) {
		for (int i = 0; i < allSpecies.size(); i++) {
			allSpecies[i].CreateNewGeneration(GetRepresentativesForEvaluation(i));
		}
		UpdateSpeciesRepresentatives();
		UpdateCurrentFitness();
		if (previousFitness != currentFitness) {
			std::cout << currentFitness << std::endl;
		}
	}
}

void CoevolutionAlgorithm::InitializeFirstIteration() {
	Species species;
	species.InitializeNewSpecies();
	allSpecies.push_back(species);
}

std::vector<Agent> CoevolutionAlgorithm::GetRepresentativesForEvaluation(int indexToOmit) {
	std::vector<Agent> representatives;

	for (int i = 0; i < allSpecies.size(); i++) {
		if (i != indexToOmit) {
			representatives.push_back(allSpecies[i].representative);
		}
	}
	return representatives;
};

void CoevolutionAlgorithm::UpdateSpeciesRepresentatives() {
	for (Species &species : allSpecies) {
		species.UpdateRepresentative();
	}
}

void CoevolutionAlgorithm::UpdateCurrentFitness() {
	std::vector<Agent> representatives = GetRepresentativesForEvaluation(-1);
	Simulation simulation;
	simulation.RunSimulation(representatives);
	simulation.CalculateFitness();
	previousFitness = currentFitness;
	currentFitness = simulation.fitness;
}