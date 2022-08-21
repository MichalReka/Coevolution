#include<iostream>
#include "CoevolutionAlgorithm.h"
#include <jsoncons/json.hpp>
#include <jsoncons/json_type_traits.hpp>

#include <fstream>
// Declare the traits. Specify which data members need to be serialized.
JSONCONS_ALL_MEMBER_NAME_TRAITS(RunData, (fitness, "fitness"),
	(productTransferedPerAgent, "productTransferedPerAgent"),
	(energyTransferedPerAgent, "energyTransferedPerAgent"));

JSONCONS_ALL_MEMBER_NAME_TRAITS(Archive, (maxFitnessRunDataPerSpecies, "maxFitnessRunDataPerSpecies"),
	(maxFitnessesRunDataPerSpeciesPerIteration, "maxFitnessesRunDataPerSpeciesPerIteration"),
	(bestFitnessOverall, "bestFitnessOverall"));
namespace jc = jsoncons;
//void Draw(sf::RenderWindow& window, std::vector<Creature>& creatures)
//{
//    sf::VertexArray arr = sf::VertexArray();
//    arr.setPrimitiveType(sf::Quads);
//    arr.resize(creatures.size() * 4);
//
//    concurrency::parallel_for(0, (int)creatures.size(), [&creatures, &arr](int i) {
//        auto size = creatures[i].shape.getSize();
//        auto position = creatures[i].shape.getPosition();
//        auto color = creatures[i].shape.getFillColor();
//
//        sf::Vertex* quad = &arr[i * 4];
//        quad[0].position = sf::Vector2f(position.x, position.y);
//        quad[1].position = sf::Vector2f(position.x + size.x, position.y);
//        quad[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
//        quad[3].position = sf::Vector2f(position.x, position.y + size.y);
//
//        quad[0].color = color;
//        quad[1].color = color;
//        quad[2].color = color;
//        quad[3].color = color;
//        });
//    //for (auto& creature : creatures)
//    //{
//    //    auto size = creature.shape.getSize();
//    //    auto position = creature.shape.getPosition();
//    //    auto color = creature.shape.getFillColor();
//
//    //    sf::Vertex* quad = &arr[i * 4];
//    //    quad[0].position = sf::Vector2f(position.x, position.y);
//    //    quad[1].position = sf::Vector2f(position.x + size.x, position.y);
//    //    quad[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
//    //    quad[3].position = sf::Vector2f(position.x, position.y + size.y);
//
//    //    quad[0].color = color;
//    //    quad[1].color = color;
//    //    quad[2].color = color;
//    //    quad[3].color = color;
//
//    //    i++;
//    //}
//
//    window.draw(arr);
//}

int main() {
	srand(time(NULL));
	std::cout << "coev" << std::endl;
	std::vector<Archive> archives;

	for (int i = 0; i < 2; i++) {
		CoevolutionAlgorithm coev;
		coev.Run();
		archives.push_back(coev.archive);
	}
	
	std::string s;

	jc::encode_json_pretty(archives, s);

	std::cout << s << std::endl;

	std::ofstream out("json-test.json");
	out << s;
	out.close();
	system("C:/Users/Michal/AppData/Local/Programs/Python/Python39/python.exe present-data.py");
	return 0;
}