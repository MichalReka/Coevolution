#include <map>
#pragma once
struct SimulationRuntimeData {
public:
	std::map<Agent*, Agent> productRequesters;
	std::map<Agent*, Agent> energyRequesters;
};