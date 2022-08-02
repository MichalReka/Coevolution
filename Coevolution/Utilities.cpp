#include "Utilities.h"

float Utilities::GetRandomFloat()
{
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0, 1);
    return dis(e);
}

bool Utilities::IsNear(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
    float xDif = vector1.x - vector2.x;
    float yDif = vector1.y - vector2.y;
    return sqrt(pow(xDif, 2) + pow(yDif, 2)) <= 1;
}

void Utilities::NormalizeVector(sf::Vector2f& v)
{
	auto sum = std::sqrt(v.x * v.x + v.y * v.y);
    v.x = v.x / sum;
    v.y = v.y / sum;
}

float Utilities::ConvertRange(float min, float max, float newMin, float newMax, float value)
{
    float range = (max - min);
    float newRange = (newMax - newMin);
    float newValue = (((value - min) * newRange) / range) + newMin;
    return newValue;
}
