//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// stat debuff
//

#pragma once

#include <string>

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class StatDebuff : public IStatus
	{
	public:
		StatDebuff(std::string stat, float lifeTime, StatsManager *statsManager);
		~StatDebuff();
	public:
		bool update(float deltaTime);
		bool isStatus(Status status) const;
		bool canMove() const;
	private:
		std::string _stat;
		float _lifeTime;
		StatsManager *_statsManager;
	};
}