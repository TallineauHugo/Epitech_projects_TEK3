//
// EPITECH PROJECT, 2019
// statbuff
// File description:
// pocket dungeon
//

#pragma once

#include <string>

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class StatBuff : public IStatus
	{
	public:
		StatBuff(std::string stat, float lifeTime, StatsManager *statsManager);
		~StatBuff();
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