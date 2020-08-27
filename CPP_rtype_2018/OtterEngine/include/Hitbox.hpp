#include <SFML/System.hpp>
#include "define.hpp"

#pragma once

class OtterEngine::Hitbox {

public:
        enum Type {
		CIRCLE = 1,
		SQUARE
	};
	
	Hitbox();
	~Hitbox();

	// Getters and Setters

	void setAngle(double angle);
	void setPos(Vector2d pos);
	void setType(OtterEngine::Hitbox::Type type);
	void setSquareSize(Vector2d squareSize);
	void setRadius(int radius);
	double getAngle();
	Vector2d& getPos();
	OtterEngine::Hitbox::Type getType();
	Vector2d getSquareSize();
	int getRadius();
	void applyLPos();
	
	// Methods
	
	bool doCollide(OtterEngine::Hitbox hitbox);
	
	
private:
	int _angle;
	Vector2d _pos;
	Vector2d _lpos;
	OtterEngine::Hitbox::Type _type;
	Vector2d _squareSize;
	int _radius;
	
};
