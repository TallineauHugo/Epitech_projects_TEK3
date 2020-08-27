#include "Object.hpp"

#pragma once

class CooldownReduc : public virtual OtterEngine::Object
{
public:
	CooldownReduc(Vector2d);
	~CooldownReduc();

	void updateEvents(OtterEngine::Engine *);
    
private:
	std::vector<OtterEngine::Event<CooldownReduc>> _events;
};
