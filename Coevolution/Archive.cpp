#include "Archive.h"

void Archive::UpdateMaxFitnessRunData(RunData& runData, int speciesNumber)
{
	if (maxFitnessRunDataPerSpecies.size() < speciesNumber) {
		maxFitnessRunDataPerSpecies.push_back(runData);
		std::vector<RunData> v;
		v.push_back(runData);
		maxFitnessesRunDataPerSpeciesPerIteration.push_back(v);
	}
	else if (runData.fitness > maxFitnessRunDataPerSpecies[speciesNumber - 1].fitness) {
		maxFitnessRunDataPerSpecies[speciesNumber - 1] = runData;
		maxFitnessesRunDataPerSpeciesPerIteration[speciesNumber - 1].push_back(runData);
	}
}

void Archive::UpdateBestTeam(std::vector<Agent> teamCandidate, float fitnessCandidate)
{
	if (fitnessCandidate > bestFitnessOverall) {
		bestFitnessOverall = fitnessCandidate;
		bestTeam = teamCandidate;
	}
}

RunData RunData::ExtractRunDataFromSimulation(Simulation& simulation)
{
	RunData runData;
	runData.fitness = simulation.productsGatheredPerAgent;
	runData.productTransferedPerAgent = simulation.productTransferedPerAgent;
	runData.energyTransferedPerAgent = simulation.energyTransferedPerAgent;
	return runData;
}
