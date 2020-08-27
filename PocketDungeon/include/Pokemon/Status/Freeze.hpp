//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// freeze
//

#pragma once

#include "IStatus.hpp"

class StatsManager;

namespace Status {
	class Freeze : public IStatus
	{
	public:
		Freeze(Status status, float lifeTime, StatsManager *statsManager);
		~Freeze();
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