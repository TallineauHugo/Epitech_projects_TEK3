#include <SFML/System.hpp>

#pragma once

class TimeManager
{
public:
	static TimeManager *getInstance() {
		static TimeManager instance;

		return &instance;
	}
	~TimeManager();

	void update();
	float getDeltaTime();
	float getTotalTime();

private:
	TimeManager();

	sf::Clock _clock;
	float _deltaTime;
	float _totalTime;
};