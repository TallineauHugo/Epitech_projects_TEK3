//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// sleep
//

#pragma once

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class Sleep : public IStatus
	{
	public:
		Sleep(Status status, float lifeTime, StatsManager *statsManager);
		~Sleep();
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