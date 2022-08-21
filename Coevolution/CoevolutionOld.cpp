// Coevolution.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "CreatureOld.cpp"
#include <random>
#include <ppl.h>
#include <array>

void SeedCreatures(sf::RenderWindow& window, std::vector<Creature>& creatures)
{
    int size = 200000;

    for (int i = 0; i < size; i++)
    {
        creatures.push_back(Creature(window.getSize().x, window.getSize().y));
    }
}

void Move(int start, int end, std::vector<Creature>& creatures)
{
    for (int i = start; i < end; i++)
    { 
        creatures[i].Move();
    }
}

void Draw(sf::RenderWindow& window, std::vector<Creature>& creatures)
{
    sf::VertexArray arr = sf::VertexArray();
    arr.setPrimitiveType(sf::Quads);
    arr.resize(creatures.size() * 4);

    concurrency::parallel_for(0, (int)creatures.size(), [&creatures, &arr](int i) {
        auto size = creatures[i].shape.getSize();
        auto position = creatures[i].shape.getPosition();
        auto color = creatures[i].shape.getFillColor();

        sf::Vertex* quad = &arr[i * 4];
        quad[0].position = sf::Vector2f(position.x, position.y);
        quad[1].position = sf::Vector2f(position.x + size.x, position.y);
        quad[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
        quad[3].position = sf::Vector2f(position.x, position.y + size.y);

        quad[0].color = color;
        quad[1].color = color;
        quad[2].color = color;
        quad[3].color = color;
     });
    //for (auto& creature : creatures)
    //{
    //    auto size = creature.shape.getSize();
    //    auto position = creature.shape.getPosition();
    //    auto color = creature.shape.getFillColor();

    //    sf::Vertex* quad = &arr[i * 4];
    //    quad[0].position = sf::Vector2f(position.x, position.y);
    //    quad[1].position = sf::Vector2f(position.x + size.x, position.y);
    //    quad[2].position = sf::Vector2f(position.x + size.x, position.y + size.y);
    //    quad[3].position = sf::Vector2f(position.x, position.y + size.y);

    //    quad[0].color = color;
    //    quad[1].color = color;
    //    quad[2].color = color;
    //    quad[3].color = color;

    //    i++;
    //}

    window.draw(arr);
}

int mainOld()
{
    srand(time(NULL));

    const int NO_THREADS = 12;
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    std::vector<Creature> creatures;
    SeedCreatures(window, creatures);

    int creaturesPerThread = creatures.size() / NO_THREADS;
    window.setFramerateLimit(72);

    sf::Clock clock;
    float lastTime = 0;
    std::cout << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        std::vector<std::thread> threads;

        for (int i = 0; i < NO_THREADS; i++) {

            threads.push_back(std::thread(Move, 
                i * creaturesPerThread, 
                (i + 1) * creaturesPerThread < creatures.size() ? (i + 1) * creaturesPerThread : creatures.size()+1,
                std::ref(creatures)));

            //Move(i * creaturesPerThread,
            //    (i + 1) * creaturesPerThread < creatures.size() ? (i + 1) * creaturesPerThread : creatures.size(),
            //    std::ref(creatures));
        }

        for (auto& th : threads) {
            th.join();
        }

        Draw(window, creatures);

        window.display();
    }

    return 0;
}

