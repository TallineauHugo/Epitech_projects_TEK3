//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// status manager
//

#pragma once

#include <list>

#include "IStatus.hpp"
#include "Status.hpp"

class StatsManager;

namespace Status {

	class StatusManager
	{
	public:
		StatusManager();
		~StatusManager();
	public:
		bool haveStatus(Status status) const;
		bool applyStatusFor(Status status, float seconds);
		bool canMove() const;
		void setStatsManager(StatsManager *manager);
		void update(float deltaTime);
	private:
		IStatus *_currentStatus;
		std::list<IStatus *> _secondaryStatus;
		StatsManager *_statsManager;
	};

}