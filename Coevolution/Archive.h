#pragma once
#include <vector>
#include "Agent.h"
class Archive
{
public:
	std::vector<float> maxFitnessPerSpeciesNumber;
	std::vector<Agent> bestTeam;
	float bestFitnessOverall = 0;

	void UpdateMaxFitnessPerSpeciesNumber(float fitness, int speciesNumber);
	void UpdateBestTeam(std::vector<Agent> teamCandidate, float fitness);
};

