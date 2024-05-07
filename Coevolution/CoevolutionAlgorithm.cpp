#include "CoevolutionAlgorithm.h"

void CoevolutionAlgorithm::Run() {
	AddNewSpecies();
	for (currentIteration; currentIteration < maxIterations; currentIteration++) {
		for (int j = 0; j < allSpecies.size(); j++) {
			std::vector<Agent> representatives = GetRepresentatives(j);
			allSpecies[j].CreateNewGeneration(representatives);
		}
		UpdateSpeciesRepresentatives();

		std::vector<Agent> representatives = GetBestRepresentatives();
		std::cout << "Ocena: " 
			<< currentFitness 
			<<", Iter.: "
			<< currentIteration
			<< ", Iter. stagnacji: " 
			<< stagnateIterations 
			<< ", Transfery energii: " 
			<< currentBestSimulationRunData.energyTransferedPerAgent 
			<< ", Transfery produktu: " 
			<< currentBestSimulationRunData.productTransferedPerAgent
			<< std::endl;

		if (previousFitness != currentFitness) {
			archive.UpdateBestTeam(representatives, currentFitness);
			archive.UpdateMaxFitnessRunData(currentBestSimulationRunData, representatives.size());
		}

		HandleStagnation();
	}
	RunGraphicSimulation();


}

void CoevolutionAlgorithm::AddNewSpecies() {
	Species species;
	species.InitializeNewSpecies();
	allSpecies.push_back(species);
}

void CoevolutionAlgorithm::HandleStagnation()
{
	if (CheckIfStagnateIteration()) {
		++stagnateIterations;
	}
	else {
		stagnateIterations = 0;
	}
	if (stagnateIterations == STAGNATE_THRESHOLD_PER_SPECIES * allSpecies.size()) {
		if (allSpecies.size() == 3) {
			auto x = 1;
		}
		std::vector<Agent> representatives = GetRepresentatives(-1);
		DeleteUnproductiveSpecies(representatives);
		representatives = GetRepresentatives(-1);
		ShiftSimilarSpecies(representatives);
		if (allSpecies.size() < 3) {
			AddNewSpecies();
			std::cout << "DODANO NOWY GATUNEK!" << std::endl;
		}
		std::cout << "ZMIANA GATUNKOW! LICZBA GATUNKOW: " << allSpecies.size() << std::endl;
		stagnateIterations = 0;
	}
}

bool CoevolutionAlgorithm::CheckIfStagnateIteration()
{
	return (currentFitness - previousFitness) <= (previousFitness * STAGNATE_FACTOR);
}

bool CoevolutionAlgorithm::DeleteUnproductiveSpecies(std::vector<Agent>& representatives)
{
	int representativesSize = representatives.size();
	float highestFitness = -1;
	int indexToDelete = -1;

	if (representativesSize == 1)
	{
		return false;
	}

	for (int i = 0; i < representativesSize; i++) {
		std::vector<Agent> copyOfRepresentatives = std::vector<Agent>(representatives);
		Simulation simulation;

		copyOfRepresentatives.erase(copyOfRepresentatives.begin() + i);

		simulation.RunSimulation(copyOfRepresentatives);
		simulation.CalculateFitness();

		if (currentFitness < simulation.fitness
			&& archive.maxFitnessRunDataPerSpecies[representativesSize - 2].fitness < simulation.fitness
			&& highestFitness < simulation.fitness) {
			highestFitness = simulation.fitness;
			indexToDelete = i;
		}
	}

	if (indexToDelete != -1) {
		allSpecies.erase(allSpecies.begin() + indexToDelete);
		std::cout << "USUNIETO NIEPRODUKTYWNY GATUNEK" << std::endl;
		return true;
	}
	return false;
}

void CoevolutionAlgorithm::ShiftSimilarSpecies(std::vector<Agent>& representatives)
{
	int representativesSize = representatives.size();
	float highestFitness = -1;
	int indexToPreserve = -1;

	if (representativesSize == 1)
	{
		return;
	}

	for (int i = 0; i < representativesSize; i++) {
		std::vector<Agent> copyOfRepresentatives = std::vector<Agent>(representatives);
		Simulation simulation;

		copyOfRepresentatives.erase(copyOfRepresentatives.begin() + i);

		simulation.RunSimulation(copyOfRepresentatives);
		simulation.CalculateFitness();

		if (highestFitness < simulation.fitness) {
			RunData runData = RunData::ExtractRunData(simulation, currentIteration);

			archive.UpdateMaxFitnessRunData(runData, copyOfRepresentatives.size());
			highestFitness = simulation.fitness;
			indexToPreserve = i;
		}
	}

	for (int i = 0; i < representativesSize; i++) {
		std::vector<Agent> copyOfRepresentatives = std::vector<Agent>(representatives);
		Simulation simulation;

		copyOfRepresentatives.erase(copyOfRepresentatives.begin() + i);

		simulation.RunSimulation(copyOfRepresentatives);
		simulation.CalculateFitness();

		if (i != indexToPreserve && highestFitness == simulation.fitness && allSpecies.size() > 1) {
			allSpecies.erase(allSpecies.begin() + i);
			AddNewSpecies();
			std::cout << "USUNIECIE PODOBNEGO GATUNKU" << std::endl;
			return;
		}
	}
}

std::vector<Agent> CoevolutionAlgorithm::GetRepresentatives(int indexToOmit) {
	std::vector<Agent> representatives;

	for (int i = 0; i < allSpecies.size(); i++) {
		if (i != indexToOmit) {
			representatives.push_back(allSpecies[i].population[allSpecies[i].representativeIndex]);
		}
	}
	return representatives;
}

void CoevolutionAlgorithm::RunGraphicSimulation()
{
	std::vector<Agent> representatives = GetRepresentatives(-1);

	Simulation simulation;
	simulation.RunSimulation(representatives, true);
}

void CoevolutionAlgorithm::UpdateSpeciesRepresentatives() {
	for (Species& species : allSpecies) {
		species.UpdateRepresentative();
	}
}

std::vector<Agent> CoevolutionAlgorithm::GetBestRepresentatives() {
	previousFitness = currentFitness;
	std::vector<Agent> representatives = GetRepresentatives(-1);

	Simulation simulation;
	simulation.RunSimulation(representatives);
	simulation.CalculateFitness();

	currentFitness = simulation.fitness;
	currentBestSimulationRunData = RunData::ExtractRunData(simulation, currentIteration);
	return representatives;
}