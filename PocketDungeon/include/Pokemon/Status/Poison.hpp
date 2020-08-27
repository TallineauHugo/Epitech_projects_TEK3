//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// poison
//

#pragma once

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class Poison : public IStatus
	{
	public:
		Poison(Status status, float lifeTime, StatsManager *statsManager);
		~Poison();
	public:
		bool update(float deltaTime);
		bool isStatus(Status status) const;
		bool canMove() const;
	private:
		Status _status;
		float _lifeTime;
		StatsManager *_statsManager;
	};
}