//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// paralysis
//

#pragma once

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class Paralysis : public IStatus
	{
	public:
		Paralysis(Status status, float lifeTime, StatsManager *statsManager);
		~Paralysis();
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