#include "Archive.h"

void Archive::UpdateMaxFitnessPerSpeciesNumber(float fitness, int speciesNumber)
{
	if (maxFitnessPerSpeciesNumber.size() < speciesNumber) {
		maxFitnessPerSpeciesNumber.push_back(fitness);
	}
	else if (fitness > maxFitnessPerSpeciesNumber[speciesNumber - 1]) {
		maxFitnessPerSpeciesNumber[speciesNumber - 1] = fitness;
	}
}

void Archive::UpdateBestTeam(std::vector<Agent> teamCandidate, float fitnessCandidate)
{
	if (fitnessCandidate > bestFitnessOverall) {
		bestFitnessOverall = fitnessCandidate;
		bestTeam = teamCandidate;
	}
}
