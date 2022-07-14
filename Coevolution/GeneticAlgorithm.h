#pragma once
#include "Agent.h"
#include <vector>

class GeneticAlgorithm
{
public:
	Agent eliteIndividual;
	std::vector<Agent> CreateNewGeneration(std::vector<Agent> population, std::vector<Agent> representatives) {};
private:
	Agent Evaluate(Agent* agent, std::vector<Agent> representatives) {};
	Agent Mutate(Agent* agent) {};
	Agent Recombinate(Agent* firstParent, Agent* secondParent) {};
	Agent SelectParent(std::vector<Agent> population, Agent* anotherParent = NULL) {}
};

