#include "CoevolutionAlgorithm.h"

void CoevolutionAlgorithm::Run() {
	AddNewSpecies();
	//DO ZROBIENIA - ZROBIC MOCK W KTORYM ZWIEKSZANA JEST ILOSC GATUNKOW PO WYKRYCIU STAGNACJI
	for (int i = 0; i < maxIterations; i++) {
		for (int j = 0; j < allSpecies.size(); j++) {
			std::vector<Agent> representatives = GetRepresentatives(j);
			allSpecies[j].CreateNewGeneration(representatives);
		}
		UpdateSpeciesRepresentatives();

		std::vector<Agent> representatives = GetRepresentatives(-1);
		std::cout << currentFitness << " " << stagnateIterations << std::endl;
		UpdateCurrentFitness(representatives);
		if (previousFitness != currentFitness) {
			archive.UpdateBestTeam(representatives, currentFitness);
			archive.UpdateMaxFitnessPerSpeciesNumber(currentFitness, representatives.size());
		}
		HandleStagnation(representatives);
	}
}

void CoevolutionAlgorithm::AddNewSpecies() {
	Species species;
	species.InitializeNewSpecies();
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
			AddNewSpecies();
			//std::cout << "DODANIE NOWEGO GATUNKU! LICZBA GATUNKOW: "<< allSpecies.size() << std::endl;
		}
		else {
			allSpecies.erase(allSpecies.begin() + speciesIndexToDelete);
			//std::cout << "USUNIECIE GATUNKU! LICZBA GATUNKOW: "<< allSpecies.size() << std::endl;
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
	float highestFitness = 0;
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
		if (archive.maxFitnessPerSpeciesNumber[allSpecies.size()-1] < simulation.fitness && highestFitness < simulation.fitness) {
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
			representatives.push_back(allSpecies[i].representative);
		}
	}
	return representatives;
};

void CoevolutionAlgorithm::UpdateSpeciesRepresentatives() {
	for (Species& species : allSpecies) {
		species.UpdateRepresentative();
	}
}

void CoevolutionAlgorithm::UpdateCurrentFitness(std::vector<Agent>& representatives) {
	Simulation simulation;
	simulation.RunSimulation(representatives);
	simulation.CalculateFitness();
	previousFitness = currentFitness;
	currentFitness = simulation.fitness;
}