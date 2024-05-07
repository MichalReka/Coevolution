#include "Simulation.h"

void Simulation::RunSimulation(std::vector<Agent>& agentTemplates, bool graphic) {
	////MOCK
	//MockSimulation(agentTemplates);
	////MOCK
	std::unique_ptr<sf::RenderWindow> window;
	if (graphic) {
		window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(Environment::SIMULATION_GRAPH_SIZE.x, Environment::SIMULATION_GRAPH_SIZE.y), "Simulation"));
		Environment::MAX_ENERGY_PER_AGENT = Environment::MAX_ENERGY_PER_AGENT * 320;
		Environment::AGENT_SPEED = 0.1f;
	}

	std::vector<Agent> realAgents;

	for (Agent& agentTemplate : agentTemplates) {
		for (int i = 0; i < agentTemplate.agentTemplateSize; i++) {
			Agent realAgent = agentTemplate;
			realAgent.position = Environment::SPAWN_POSITION;
			realAgents.push_back(realAgent);
		}
	}
	bool sleep = true;
	for (int i = 0; i < SIMULATION_MAX_ITERATIONS; i++)
	{
		for (Agent& agent : realAgents) {
			agent.DetectEvent(runtimeData.productRequesters, runtimeData.energyRequesters);
		}

		for (Agent& agent : realAgents) {
			agent.PerformAction(runtimeData.productRequesters, runtimeData.energyRequesters);
		}

		if (graphic) {
			i = 0;
			window->clear();

			DrawSimulationIter(*window, realAgents);

			window->display();
		}
	}

	for (Agent& agent : realAgents) {
		productsGatheredPerAgent = productsGatheredPerAgent + agent.totalProductGathered;
		productTransferedPerAgent = productTransferedPerAgent + agent.productTransfered;
		energyTransferedPerAgent = energyTransferedPerAgent + agent.energyTransfered;
	}

	productsGatheredPerAgent = productsGatheredPerAgent / realAgents.size();
	productTransferedPerAgent = productTransferedPerAgent / realAgents.size();
	energyTransferedPerAgent = energyTransferedPerAgent / realAgents.size();
	
	if (energyTransferedPerAgent > 0) {
		auto x = 0;
	}
}
std::thread Simulation::CreateSimulationThread(std::vector<Agent>& agentTemplates)
{
	return std::thread();
}

void Simulation::MockSimulation(std::vector<Agent> agentTemplates) {
	//energySpentPerAgent = 1;
	//productsGatheredPerAgent = 0;
	//for (int i = 0; i < 9; i++) {
	//	for (int j = 0; j < 7; j++)
	//	{
	//		int responseSum = 0;
	//		for (const Agent &agent : agentTemplates) {
	//			responseSum = agent.responses[i][j] + responseSum;
	//			productsGatheredPerAgent = (responseSum % 4 == 0) + productsGatheredPerAgent;
	//		}
	//	}
	//}
	//productsGatheredPerAgent = productsGatheredPerAgent / agentTemplates.size();
}

void Simulation::CalculateFitness() {
	fitness = productsGatheredPerAgent / energySpentPerAgent;
}

void Simulation::DrawSimulationIter(sf::RenderWindow& window, std::vector<Agent>& agents)
{
	sf::VertexArray arr = sf::VertexArray();
	arr.setPrimitiveType(sf::Quads);
	arr.resize(agents.size() * 4 + 12);
	int i = 0;

	auto size = sf::Vector2f(50, 50);
	auto position = Environment::ENERGY_REFILL_POSITION;
	auto color = sf::Color().Blue;

	sf::Vertex* refill = &arr[i * 4];
	refill[0].position = sf::Vector2f(position.x, position.y);
	refill[1].position = sf::Vector2f(position.x + size.x, position.y);
	refill[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
	refill[3].position = sf::Vector2f(position.x, position.y + size.y);

	refill[0].color = color;
	refill[1].color = color;
	refill[2].color = color;
	refill[3].color = color;

	i++;

	size = sf::Vector2f(50, 50);
	position = Environment::PRODUCT_DROP_POSITION;
	color = sf::Color().Cyan;

	sf::Vertex* drop = &arr[i * 4];
	drop[0].position = sf::Vector2f(position.x, position.y);
	drop[1].position = sf::Vector2f(position.x + size.x, position.y);
	drop[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
	drop[3].position = sf::Vector2f(position.x, position.y + size.y);

	drop[0].color = color;
	drop[1].color = color;
	drop[2].color = color;
	drop[3].color = color;

	i++;

	size = sf::Vector2f(50, 50);
	position = Environment::PRODUCT_TAKE_POSITION;
	color = sf::Color().Red;

	sf::Vertex* take = &arr[i * 4];
	take[0].position = sf::Vector2f(position.x, position.y);
	take[1].position = sf::Vector2f(position.x + size.x, position.y);
	take[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
	take[3].position = sf::Vector2f(position.x, position.y + size.y);

	take[0].color = color;
	take[1].color = color;
	take[2].color = color;
	take[3].color = color;

	i++;

	for (auto& agent : agents)
	{
		auto size = sf::Vector2f(32,32);
		auto position = agent.position;
		auto color = sf::Color().Yellow;

		sf::Vertex* quad = &arr[i * 4];
		quad[0].position = sf::Vector2f(position.x, position.y);
		quad[1].position = sf::Vector2f(position.x + size.x, position.y);
		quad[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
		quad[3].position = sf::Vector2f(position.x, position.y + size.y);

		quad[0].color = color;
		quad[1].color = color;
		quad[2].color = color;
		quad[3].color = color;

		i++;
	}

	window.draw(arr);
}