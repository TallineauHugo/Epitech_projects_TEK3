//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// IStatus
//

#pragma once

#include "Status.hpp"

class StatsManager;

namespace Status {

	class IStatus
	{
	public:
		virtual ~IStatus() = default;
	public:
		virtual bool update(float deltaTime) = 0;
		virtual bool isStatus(Status status) const = 0;
		virtual bool canMove() const = 0;
	};

}