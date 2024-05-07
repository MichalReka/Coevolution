#include "Archive.h"
Archive::Archive() {

	maxFitnessRunDataPerSpecies.push_back(RunData());
	maxFitnessRunDataPerSpecies.push_back(RunData());
	maxFitnessRunDataPerSpecies.push_back(RunData());
}

void Archive::UpdateMaxFitnessRunData(RunData& runData, int speciesNumber)
{
	if (runData.fitness >= maxFitnessRunDataPerSpecies[speciesNumber - 1].fitness) {
		maxFitnessRunDataPerSpecies[speciesNumber - 1] = runData;
		if (maxFitnessesRunDataPerSpeciesPerIteration.size() < speciesNumber) {
			std::vector<RunData> v;
			v.push_back(runData);
			maxFitnessesRunDataPerSpeciesPerIteration.push_back(v);
		}
		else{
			maxFitnessesRunDataPerSpeciesPerIteration[speciesNumber - 1].push_back(runData);
		}
	}
}

void Archive::UpdateBestTeam(std::vector<Agent> teamCandidate, float fitnessCandidate)
{
	if (fitnessCandidate > bestFitnessOverall) {
		bestFitnessOverall = fitnessCandidate;
		bestTeam = teamCandidate;
	}
}

RunData RunData::ExtractRunData(Simulation& simulation, int iteration)
{
	RunData runData;
	runData.fitness = simulation.productsGatheredPerAgent;
	runData.productTransferedPerAgent = simulation.productTransferedPerAgent;
	runData.energyTransferedPerAgent = simulation.energyTransferedPerAgent;
	runData.coevIteration = iteration;
	return runData;
}
