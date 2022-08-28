#pragma once
#include <vector>
#include <iostream>
#include "Species.h"
#include "Archive.h"
class CoevolutionAlgorithm
{
	//TODO: ARCHIWUM, MECHANIZM WYKRYWANIA STAGNACJI I DODAWANIA/USUWANIA GATUNK�W!
public:
	const double STAGNATE_FACTOR = 0.01;
	const int STAGNATE_THRESHOLD_PER_SPECIES = 35;

	float currentFitness = -1;
	float previousFitness = -1;
	int stagnateIterations = 0;

	int maxIterations = 800;
	std::vector<Species> allSpecies;
	std::vector<Species> bestSpeciesSet;
	Archive archive;
	RunData currentBestSimulationRunData;
	void Run();
private:
	void AddNewSpecies();
	void HandleStagnation();
	bool CheckIfStagnateIteration();
	bool DeleteUnproductiveSpecies(std::vector<Agent>& representatives);
	void ShiftSimilarSpecies(std::vector<Agent>& representatives);
	std::vector<Agent> GetBestRepresentatives(int iteration);
	void UpdateSpeciesRepresentatives();
	std::vector<Agent> GetRepresentatives(int indexToOmit);
};
