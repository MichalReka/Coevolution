#include <random>
#include <SFML/Graphics.hpp>
#include <cmath>

#pragma once
class Utilities {
public:
	static float GetRandomFloat();
	static bool IsNear(sf::Vector2f& vector1, sf::Vector2f& vector2, float offset = 64);
	static double GetVectorLength(double x, double y);
	static void NormalizeVector(sf::Vector2f& v);
	static float ConvertRange(float min, float max, float newMin, float newMax, float value);
};
