#include "Environment.h"

sf::Vector2f Environment::SPAWN_POSITION = sf::Vector2f(2, 2);
sf::Vector2f Environment::ENERGY_REFILL_POSITION = sf::Vector2f(1, 1);
sf::Vector2f Environment::SIMULATION_GRAPH_SIZE = sf::Vector2f(25, 25);
sf::Vector2f Environment::PRODUCT_DROP_POSITION = sf::Vector2f(20, 1);
sf::Vector2f Environment::PRODUCT_TAKE_POSITION = sf::Vector2f(1, 20);
float Environment::MAX_PRODUCT_PER_AGENT = 100;
float Environment::MAX_PRODUCT_ENERGY_SLOWUP = 18;
float Environment::MAX_PRODUCT_SLOWUP = 15;
float Environment::ZERO_ENERGY_SLOWUP = 1;
float Environment::MAX_ENERGY_PER_AGENT = 250;
int Environment::MAX_AGENTS_PER_TEMPLATE = 3;