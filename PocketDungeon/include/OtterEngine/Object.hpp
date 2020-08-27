#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Hitbox.hpp"
#include "Event.hpp"

namespace OtterEngine {

	class ISprite;

	class Object {

	public:
		Object(std::size_t id = 0);
		~Object();

		// Getters and Setters

		void setPos(Vector2d pos);
		void setAim(Vector2d aim);
		void setHitBox(OtterEngine::Hitbox hitbox);
		void setVelocity(Vector2d velocity);
		Vector2d &getPos();
		Vector2d &getAim();
		virtual Vector2d getSize();
		int getAngle();
		void setAngle(int);
		OtterEngine::Hitbox &getHitbox();
		Vector2d &getVelocity();
		std::string getName();
		ISprite *getSprite();
		std::size_t getId() const;
		void setIsPlayer(bool);
		bool getIsPlayer(void);
		void setName(std::string);
		// Methods

		virtual void updateEvents(OtterEngine::Engine *);
		void applyVelocity();
	protected:
		std::string _name;
		OtterEngine::Hitbox _hitbox;
		Vector2d _velocity;
		std::vector<OtterEngine::Event<OtterEngine::Object>> _events;
		ISprite *_sprite;
		Vector2d _aim;
		bool _isPlayer;
	private:
		std::size_t _id;
	};
}
