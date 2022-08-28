#pragma once
#include <vector>
#include "Agent.h"
#include "Simulation.h"

struct RunData {
	float fitness;
	float productTransferedPerAgent = 0;
	float energyTransferedPerAgent = 0;
	int coevIteration = 0;

	static RunData ExtractRunData(Simulation& simulation, int iteration);
};

class Archive
{
public:
	std::vector<RunData> maxFitnessRunDataPerSpecies;
	std::vector<std::vector<RunData>> maxFitnessesRunDataPerSpeciesPerIteration;
	std::vector<Agent> bestTeam;
	float bestFitnessOverall = 0;

	void UpdateMaxFitnessRunData(RunData& runData, int speciesNumber);
	void UpdateBestTeam(std::vector<Agent> teamCandidate, float fitness);
};