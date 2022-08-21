#pragma once
#include <vector>
#include <iostream>
#include "Species.h"
#include "Archive.h"
class CoevolutionAlgorithm
{
	//TODO: ARCHIWUM, MECHANIZM WYKRYWANIA STAGNACJI I DODAWANIA/USUWANIA GATUNKÓW!
public:
	const double STAGNATE_FACTOR = 0.01;
	const int STAGNATE_THRESHOLD_PER_SPECIES = 35;

	float currentFitness = 0;
	float previousFitness = 0;
	int stagnateIterations = 0;

	int maxIterations = 500;
	std::vector<Species> allSpecies;
	std::vector<Species> bestSpeciesSet;
	Archive archive;
	RunData currentBestSimulationRunData;
	void Run();
private:
	void AddNewSpecies();
	void HandleStagnation(std::vector<Agent>& representatives);
	bool CheckIfStagnateIteration();
	int SpeciesIndexToDelete(std::vector<Agent>& representatives);
	std::vector<Agent> GetBestRepresentatives();
	void UpdateSpeciesRepresentatives();
	std::vector<Agent> GetRepresentatives(int indexToOmit);
};
