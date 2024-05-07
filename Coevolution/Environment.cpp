#include "Environment.h"

sf::Vector2f Environment::SPAWN_POSITION = sf::Vector2f(152, 152);
sf::Vector2f Environment::SIMULATION_GRAPH_SIZE = sf::Vector2f(850, 850);
sf::Vector2f Environment::ENERGY_REFILL_POSITION = sf::Vector2f(120, 120);
sf::Vector2f Environment::PRODUCT_DROP_POSITION = sf::Vector2f(760, 120);
sf::Vector2f Environment::PRODUCT_TAKE_POSITION = sf::Vector2f(120, 760);
float Environment::MAX_PRODUCT_ENERGY_SLOWUP = 20;
float Environment::MAX_PRODUCT_SLOWUP = 20;
float Environment::ZERO_ENERGY_SLOWUP = 1.5;
float Environment::MAX_PRODUCT_PER_AGENT = 100;
float Environment::MAX_ENERGY_PER_AGENT = 300;
float Environment::AGENT_SPEED = 32;
int Environment::MAX_AGENTS_PER_TEMPLATE = 3;