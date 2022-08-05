#include "Environment.h"

sf::Vector2f Environment::SPAWN_POSITION = sf::Vector2f(15, 15);
sf::Vector2f Environment::ENERGY_REFILL_POSITION = sf::Vector2f(30, 30);
sf::Vector2f Environment::SIMULATION_GRAPH_SIZE = sf::Vector2f(150, 150);
sf::Vector2f Environment::PRODUCT_DROP_POSITION = sf::Vector2f(140, 1);
sf::Vector2f Environment::PRODUCT_TAKE_POSITION = sf::Vector2f(1, 140);
float Environment::MAX_PRODUCT_PER_AGENT = 100;
float Environment::MAX_PRODUCT_ENERGY_MULTIPLIER = 6;
float Environment::MAX_ENERGY_PER_AGENT = 500; 
int Environment::MAX_AGENTS_PER_TEMPLATE = 5;