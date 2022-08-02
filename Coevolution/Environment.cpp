#include "Environment.h"

sf::Vector2f Environment::SPAWN_POSITION = sf::Vector2f(1, 1);
sf::Vector2f Environment::ENERGY_REFILL_POSITION = sf::Vector2f(1, 1);
sf::Vector2f Environment::SIMULATION_GRAPH_SIZE = sf::Vector2f(100, 100);
sf::Vector2f Environment::PRODUCT_DROP_POSITION = sf::Vector2f(80, 1);
sf::Vector2f Environment::PRODUCT_TAKE_POSITION = sf::Vector2f(1, 80);
float Environment::MAX_PRODUCT_PER_AGENT = 100;
float Environment::MAX_PRODUCT_ENERGY_MULTIPLIER = 3;
float Environment::MAX_ENERGY_PER_AGENT = 300;