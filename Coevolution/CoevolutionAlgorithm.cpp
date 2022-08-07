#include "CoevolutionAlgorithm.h"

void CoevolutionAlgorithm::Run() {
	AddNewSpecies();
	for (int i = 0; i < maxIterations; i++) {
		for (int j = 0; j < allSpecies.size(); j++) {
			std::vector<Agent> representatives = GetRepresentatives(j);
			allSpecies[j].CreateNewGeneration(representatives);
		}
		UpdateSpeciesRepresentatives();

		std::vector<Agent> representatives = GetBestRepresentatives();
		std::cout << currentFitness << " " << stagnateIterations << std::endl;
		if (previousFitness != currentFitness) {
			archive.UpdateBestTeam(representatives, currentFitness);
			archive.UpdateMaxFitnessPerSpeciesNumber(currentFitness, representatives.size());
		}
		HandleStagnation(representatives);
	}
}

void CoevolutionAlgorithm::AddNewSpecies(bool initial) {
	Species species;
	species.InitializeNewSpecies(initial);
	allSpecies.push_back(species);
}

void CoevolutionAlgorithm::HandleStagnation(std::vector<Agent>& representatives)
{
	if (CheckIfStagnateIteration()) {
		++stagnateIterations;
	}
	else {
		stagnateIterations = 0;
	}
	if (stagnateIterations == STAGNATE_THRESHOLD_PER_SPECIES * allSpecies.size()) {
		int speciesIndexToDelete = SpeciesIndexToDelete(representatives);
		if (speciesIndexToDelete == -1) {
			AddNewSpecies(false);
			std::cout << "DODANIE NOWEGO GATUNKU! LICZBA GATUNKOW: "<< allSpecies.size() << std::endl;
		}
		else {
			allSpecies.erase(allSpecies.begin() + speciesIndexToDelete);
			std::cout << "USUNIECIE GATUNKU! LICZBA GATUNKOW: "<< allSpecies.size() << std::endl;
		}
		stagnateIterations = 0;
	}
}

bool CoevolutionAlgorithm::CheckIfStagnateIteration()
{
	return (currentFitness - previousFitness) <= (previousFitness * STAGNATE_FACTOR);
}

int CoevolutionAlgorithm::SpeciesIndexToDelete(std::vector<Agent>& representatives)
{
	int representativesSize = representatives.size();
	float highestFitness = -1;
	int indexToDelete = -1;
	if (representativesSize == 1)
	{
		return -1;
	}

	auto linear_erase = [](auto& v, const size_t index) {
		std::swap(v[index], v.back());
		v.pop_back();
	};

	for (int i = 0; i < representativesSize; i++) {
		std::vector<Agent> copyOfRepresentatives = std::vector<Agent>(representatives);
		Simulation simulation;

		linear_erase(copyOfRepresentatives, i);
		simulation.RunSimulation(copyOfRepresentatives);
		simulation.CalculateFitness();
		if (archive.maxFitnessPerSpeciesNumber[allSpecies.size()-1] <= simulation.fitness && highestFitness <= simulation.fitness) {
			highestFitness = simulation.fitness;
			indexToDelete = i;
		}
	}
	return indexToDelete;
}

std::vector<Agent> CoevolutionAlgorithm::GetRepresentatives(int indexToOmit) {
	std::vector<Agent> representatives;

	for (int i = 0; i < allSpecies.size(); i++) {
		if (i != indexToOmit) {
			representatives.push_back(allSpecies[i].population[allSpecies[i].representativeIndex]);
		}
	}
	return representatives;
};

void CoevolutionAlgorithm::UpdateSpeciesRepresentatives() {
	for (Species& species : allSpecies) {
		species.UpdateRepresentative();
	}
}

std::vector<Agent> CoevolutionAlgorithm::GetBestRepresentatives() {
	previousFitness = currentFitness;
	float bestFitness = -1;
	std::vector<Agent> representatives;
	for (int i = 0; i < allSpecies.size(); i++)
	{
		std::vector<Agent> candidates = GetRepresentatives(i);
		candidates.push_back(allSpecies[i].population[allSpecies[i].representativeIndex]);
		Simulation simulation;
		simulation.RunSimulation(candidates);
		simulation.CalculateFitness();
		if (bestFitness < simulation.fitness) {
			representatives = candidates;
			bestFitness = simulation.fitness;
		}
	}
	
	currentFitness = bestFitness;
	return representatives;
}