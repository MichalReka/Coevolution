#include<iostream>
#include "CoevolutionAlgorithm.h"

//#include <jsoncons/json.hpp>
//#include <jsoncons/json_type_traits.hpp>
//
//#include <fstream>
//// Declare the traits. Specify which data members need to be serialized.
//JSONCONS_ALL_MEMBER_NAME_TRAITS(RunData, (fitness, "fitness"), (coevIteration, "coevIteration"),
//	(productTransferedPerAgent, "productTransferedPerAgent"),
//	(energyTransferedPerAgent, "energyTransferedPerAgent"));
//
//JSONCONS_ALL_MEMBER_NAME_TRAITS(Archive, (maxFitnessRunDataPerSpecies, "maxFitnessRunDataPerSpecies"),
//	(maxFitnessesRunDataPerSpeciesPerIteration, "maxFitnessesRunDataPerSpeciesPerIteration"),
//	(bestFitnessOverall, "bestFitnessOverall"));
//namespace jc = jsoncons;

int main() {
	srand(time(NULL));
	std::cout << "coev" << std::endl;
	std::vector<Archive> archives;

	for (int i = 0; i < 1; i++) {
		CoevolutionAlgorithm coev;
		coev.Run();
		archives.push_back(coev.archive);
	}
	
	//std::string s;

	//jc::encode_json_pretty(archives, s);

	//std::cout << s << std::endl;

	//std::ofstream out("json-test.json");
	//out << s;
	//out.close();
	return 0;
}