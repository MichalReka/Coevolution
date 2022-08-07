#include<iostream>
#include "CoevolutionAlgorithm.h"
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
	std::cout << "Hello" << std::endl;
	CoevolutionAlgorithm coev;
	coev.Run();

}