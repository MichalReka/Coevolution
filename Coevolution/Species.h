#pragma once
#include "GeneticAlgorithm.h"
class Species
{
public:
	std::vector<Agent> population;
	int representativeIndex;
	int speciesSize = 100;

	void InitializeNewSpecies();
	void CreateNewGeneration(std::vector<Agent>& foreignRepresentatives);
	void UpdateRepresentative();

    Species() = default;
    Species(Species const&) = default;
    // user-defined copy assignment (copy-and-swap idiom)
    Species& operator=(Species other)
    {
        std::swap(population, other.population);
        std::swap(representativeIndex, other.representativeIndex);
        std::swap(geneticAlgorithm, other.geneticAlgorithm);
        return *this;
    }

private:
	GeneticAlgorithm geneticAlgorithm;
};

