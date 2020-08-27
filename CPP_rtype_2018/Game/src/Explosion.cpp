#include "TimeManager.hpp"
#include "Explosion.hpp"

Explosion::Explosion(Vector2d pos, int size, CAMP camp) : Bullet(pos, Vector2d(0,0), camp)
{
	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setRadius(size);
	moment = TimeManager::getInstance()->getTotalTime();
	_name += "Explosion::";
	_sprite->loadSpriteFromFile("ressources/texture/Player.png");
	addEvent<Explosion>(_events, OtterEngine::Event<Explosion>("Finish", &Explosion::Finish, &Explosion::isFinished));
}

Explosion::~Explosion()
{

}

void Explosion::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

bool Explosion::isFinished(OtterEngine::Engine *oe)
{
	float time = TimeManager::getInstance()->getTotalTime();
	if (time - moment < 0 || time - moment > 1.5)
		return true;
	return false;
}

int Explosion::Finish(OtterEngine::Engine *oe)
{
	Bullet::hit(oe);
}

void Explosion::hit(OtterEngine::Engine *oe)
{
	
}
