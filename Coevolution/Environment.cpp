#include "Environment.h"

sf::Vector2f Environment::SPAWN_POSITION = sf::Vector2f(16, 16);
sf::Vector2f Environment::ENERGY_REFILL_POSITION = sf::Vector2f(15, 15);
sf::Vector2f Environment::SIMULATION_GRAPH_SIZE = sf::Vector2f(100, 100);
sf::Vector2f Environment::PRODUCT_DROP_POSITION = sf::Vector2f(90, 1);
sf::Vector2f Environment::PRODUCT_TAKE_POSITION = sf::Vector2f(1, 90);
float Environment::MAX_PRODUCT_PER_AGENT = 100;
float Environment::MAX_PRODUCT_ENERGY_SLOWUP = 15;
float Environment::MAX_PRODUCT_SLOWUP = 2;
float Environment::ZERO_ENERGY_SLOWUP = 10;
float Environment::MAX_ENERGY_PER_AGENT = 1000;
int Environment::MAX_AGENTS_PER_TEMPLATE = 5;