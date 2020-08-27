//
// Created by flav on 1/31/19.
//

#include <OtterEngine/TimeManager.hpp>
#include "IItems.hpp"

IItems::IItems()
: Object() {
	_launchTime = TimeManager::getInstance()->getTotalTime();
}

IItems::~IItems() {

}

