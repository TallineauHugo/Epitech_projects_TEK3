//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// burn
//

#pragma once

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class Burn : public IStatus
	{
	public:
		Burn(Status status, float lifeTime, StatsManager *statsManager);
		~Burn();
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