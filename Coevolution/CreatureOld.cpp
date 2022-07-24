#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>

class Creature {
public:

	sf::RectangleShape shape;
	sf::Vector2f destination;
	int xBorder;
	int yBorder;

private:

	bool _isMoving = false;
	float _speed = 3.f;
	std::unique_ptr<std::uniform_int_distribution<>> _xRange;
	std::unique_ptr<std::uniform_int_distribution<>> _yRange;
	std::mt19937 _gen;

public:

	Creature(int x, int y)
	{
		shape.setSize(sf::Vector2f(5, 5));
		shape.setFillColor(sf::Color::Yellow);
		xBorder = x;
		yBorder = y;
		_xRange.reset(new std::uniform_int_distribution<>(0, x - shape.getSize().x));
		_yRange.reset(new std::uniform_int_distribution<>(0, y - shape.getSize().y));
		std::random_device rd; // obtain a random number from hardware
		_gen.seed(rd()); // seed the generator
	}

	void Move()
	{
		if (!_isMoving)
		{
			SetMovementDestination();
			_isMoving = true;
		}

		if (EqualVectors(shape.getPosition(), destination))
		{
			_isMoving = false;
		}

		if (_isMoving)
		{
			sf::Vector2f movementVector = NormalizeVector(destination - shape.getPosition()) * _speed;

			shape.move(movementVector.x, movementVector.y);
		}
	}

	void SetMovementDestination()
	{
		std::random_device rd; // obtain a random number from hardware
		_gen.seed(rd()); // seed the generator
		destination.x = (*_xRange)(_gen);
		destination.y = (*_yRange)(_gen);
	}

private:
	bool EqualVectors(sf::Vector2f v1, sf::Vector2f v2)
	{
		int error = 10;
		return abs(ceil(v1.x) - ceil(v2.x)) <= error
			&& abs(ceil(v1.y) - ceil(v2.y)) <= error;
	}

	sf::Vector2f NormalizeVector(sf::Vector2f v)
	{
		auto sum = std::sqrt(v.x * v.x + v.y * v.y);
		return sf::Vector2f(v.x / sum, v.y / sum);
	}
};