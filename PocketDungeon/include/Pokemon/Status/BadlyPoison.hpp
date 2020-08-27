//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// baldy poison
//

#pragma once

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class BadlyPoison : public IStatus
	{
	public:
		BadlyPoison(Status status, float lifeTime, StatsManager *statsManager);
		~BadlyPoison();
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