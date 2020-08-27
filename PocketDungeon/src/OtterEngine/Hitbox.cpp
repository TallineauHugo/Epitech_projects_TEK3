#include "Hitbox.hpp"
#include <iostream>
#include "define.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

OtterEngine::Hitbox::Hitbox()
{
	_angle = 0;
	_squareSize = Vector2d(0, 0);
	_radius = 0;
	_pos = Vector2d(0, 0);
	_lpos = Vector2d(0, 0);
	_type = OtterEngine::Hitbox::SQUARE;
}

OtterEngine::Hitbox::~Hitbox()
{

}


void OtterEngine::Hitbox::setPos(Vector2d pos)
{
	_lpos = _pos;
	_pos = pos;
}

void OtterEngine::Hitbox::setAngle(double angle)
{
	_angle = angle;
}

Vector2d &OtterEngine::Hitbox::getPos()
{
	return _pos;
}

double OtterEngine::Hitbox::getAngle()
{
	return _angle;
}

void OtterEngine::Hitbox::setType(OtterEngine::Hitbox::Type type)
{
	_type = type;
}

void OtterEngine::Hitbox::setSquareSize(Vector2d squareSize)
{
	_squareSize = squareSize;
}

void OtterEngine::Hitbox::setRadius(int radius)
{
	_radius = radius;
}


OtterEngine::Hitbox::Type OtterEngine::Hitbox::getType()
{
	return _type;
}

Vector2d OtterEngine::Hitbox::getSquareSize()
{
	return _squareSize;
}

int OtterEngine::Hitbox::getRadius()
{
	return _radius;
}

static bool check_vertically(sf::Vector2f point1, sf::Vector2f point2, float min, float max)
{
	float tmpmax = (point1.y > point2.y) ? point1.y : point2.y;
	float tmpmin = (point1.y < point2.y) ? point1.y : point2.y;


	if (tmpmax <= max && tmpmax >= min)
		return false;
	if (tmpmin <= max && tmpmin >= min)
		return false;
	if (tmpmax >= max && tmpmin <= max)
		return false;
	if (tmpmin <= min && tmpmax >= min)
		return false;
	return true;
}

static bool check(sf::Vector2f point1, sf::Vector2f point2, float minx, float miny, float maxx, float maxy)
{
	float coef = (point2.y - point1.y) / (point2.x - point1.x);

	if (coef >= 1 || coef <= -1) {
		float tmpmax = (point1.y > point2.y) ? point1.y : point2.y;
		float tmpmin = (point1.y < point2.y) ? point1.y : point2.y;

		if (tmpmax <= maxy && tmpmax >= miny)
			return false;
		if (tmpmin <= maxy && tmpmin >= miny)
			return false;
		if (tmpmax >= maxy && tmpmin <= maxy)
			return false;
		if (tmpmin >= miny && tmpmax <= miny)
			return false;
		return true;
	}

	else {
		float tmpmax = (point1.x > point2.x) ? point1.x : point2.x;
		float tmpmin = (point1.x < point2.x) ? point1.x : point2.x;

		if (tmpmax <= maxx && tmpmax >= minx)
			return false;
		if (tmpmin <= maxx && tmpmin >= minx)
			return false;
		if (tmpmax >= maxx && tmpmin <= maxx)
			return false;
		if (tmpmin >= minx && tmpmax <= minx)
			return false;
		return true;
		
	}
}


// Et ya plus rien je vous jure monsieur le juge












































// Vous voyez je vous l'avez dit









































//Pourquoi vous continuez?


























bool OtterEngine::Hitbox::doCollide(OtterEngine::Hitbox hitbox)
{
	float angle = 2* M_PI * ((float)_angle / 360);
	if (hitbox.getType() == OtterEngine::Hitbox::SQUARE
	    && _type == OtterEngine::Hitbox::SQUARE) {
		sf::VertexArray quad(sf::Quads, 4);
		sf::VertexArray quad2(sf::Quads, 4);
		quad[0].position = sf::Vector2f(-_squareSize.x / 2, _squareSize.y / 2);
		quad[1].position = sf::Vector2f(_squareSize.x / 2, _squareSize.y / 2);
		quad[2].position = sf::Vector2f(_squareSize.x / 2, -_squareSize.y / 2);
		quad[3].position = sf::Vector2f(-_squareSize.x / 2, -_squareSize.y / 2);
		quad2[0].position = sf::Vector2f(-hitbox.getSquareSize().x / 2, hitbox.getSquareSize().y / 2);
		quad2[1].position = sf::Vector2f(hitbox.getSquareSize().x / 2, hitbox.getSquareSize().y / 2);
		quad2[2].position = sf::Vector2f(hitbox.getSquareSize().x / 2, -hitbox.getSquareSize().y / 2);
		quad2[3].position = sf::Vector2f(-hitbox.getSquareSize().x / 2, -hitbox.getSquareSize().y / 2);
		quad[0].position = sf::Vector2f(quad[0].position.x * cos(angle) - quad[0].position.y * sin(angle), (quad[0].position.x * sin(angle)) + (quad[0].position.y * cos(angle)));
		quad[1].position = sf::Vector2f(quad[1].position.x * cos(angle) - quad[1].position.y * sin(angle), quad[1].position.x * sin(angle) + quad[1].position.y * cos(angle));
		quad[2].position = sf::Vector2f(quad[2].position.x * cos(angle) - quad[2].position.y * sin(angle), quad[2].position.x * sin(angle) + quad[2].position.y * cos(angle));
		quad[3].position = sf::Vector2f(quad[3].position.x * cos(angle) - quad[3].position.y * sin(angle), quad[3].position.x * sin(angle) + quad[3].position.y * cos(angle));
		angle = 2* M_PI * ((float)hitbox.getAngle() / 360);
		quad2[0].position = sf::Vector2f(quad2[0].position.x * cos(angle) - quad2[0].position.y * sin(angle), quad2[0].position.x * sin(angle) + quad2[0].position.y * cos(angle));
		quad2[1].position = sf::Vector2f(quad2[1].position.x * cos(angle) - quad2[1].position.y * sin(angle), quad2[1].position.x * sin(angle) + quad2[1].position.y * cos(angle));
		quad2[2].position = sf::Vector2f(quad2[2].position.x * cos(angle) - quad2[2].position.y * sin(angle), quad2[2].position.x * sin(angle) + quad2[2].position.y * cos(angle));
		quad2[3].position = sf::Vector2f(quad2[3].position.x * cos(angle) - quad2[3].position.y * sin(angle), quad2[3].position.x * sin(angle) + quad2[3].position.y * cos(angle));
		quad[0].position.x += _pos.x;
		quad[0].position.y += _pos.y;
		quad[1].position.x += _pos.x;
		quad[1].position.y += _pos.y;
		quad[2].position.x += _pos.x;
		quad[2].position.y += _pos.y;
		quad[3].position.x += _pos.x;
		quad[3].position.y += _pos.y;
		quad2[0].position.x += hitbox.getPos().x;
		quad2[0].position.y += hitbox.getPos().y;
		quad2[1].position.x += hitbox.getPos().x;
		quad2[1].position.y += hitbox.getPos().y;
		quad2[2].position.x += hitbox.getPos().x;
		quad2[2].position.y += hitbox.getPos().y;
		quad2[3].position.x += hitbox.getPos().x;
		quad2[3].position.y += hitbox.getPos().y;
		float minx = quad2[0].position.x;
		float miny = quad2[0].position.y;
		float maxx = quad2[0].position.x;
		float maxy = quad2[0].position.y;

		for (int i = 1; i < 4; i++) {
			if (quad2[i].position.x < minx) minx = quad2[i].position.x;
			if (quad2[i].position.x > maxx) maxx = quad2[i].position.x;
			if (quad2[i].position.y > maxy) maxy = quad2[i].position.y;
			if (quad2[i].position.y < miny) miny = quad2[i].position.y;
		}
		if ((quad[0].position.x == quad[1].position.x && check_vertically(quad[0].position, quad[1].position, miny, maxy))
		    ^ (quad[0].position.x != quad[1].position.x && check(quad[0].position, quad[1].position, minx, miny, maxx, maxy)))
			return false;
		if ((quad[0].position.x == quad[3].position.x && check_vertically(quad[0].position, quad[3].position, miny, maxy))
		    ^ (quad[0].position.x != quad[3].position.x && check(quad[0].position, quad[3].position, minx, miny, maxx, maxy)))
			return false;
		minx = quad[0].position.x;
		miny = quad[0].position.y;
		maxx = quad[0].position.x;
		maxy = quad[0].position.y;
		for (int i = 1; i < 4; i++) {
			if (quad[i].position.x < minx) minx = quad[i].position.x;
			if (quad[i].position.x > maxx) maxx = quad[i].position.x;
			if (quad[i].position.y > maxy) maxy = quad[i].position.y;
			if (quad[i].position.y < miny) miny = quad[i].position.y;
		}
		if ((quad2[0].position.x == quad2[1].position.x && check_vertically(quad2[0].position, quad2[1].position, miny, maxy))
		    ^ (quad2[0].position.x != quad2[1].position.x && check(quad2[0].position, quad2[1].position, minx, miny, maxx, maxy)))
			return false;
		if ((quad2[0].position.x == quad2[3].position.x && check_vertically(quad2[0].position, quad2[3].position, miny, maxy))
		    ^ (quad2[0].position.x != quad2[3].position.x && check(quad2[0].position, quad2[3].position, minx, miny, maxx, maxy)))
			return false;
		return true;
	}
	
        else if (hitbox.getType() == OtterEngine::Hitbox::CIRCLE
		 && _type == OtterEngine::Hitbox::CIRCLE) {
		int distSq = (_pos.x - hitbox.getPos().x) * (_pos.x - hitbox.getPos().x) +
			(_pos.y - hitbox.getPos().y) * (_pos.y - hitbox.getPos().y);
		int radSumSq = (_radius + hitbox.getRadius()) * (_radius + hitbox.getRadius());
		if (distSq <= radSumSq)
			return true;
		else
			return false;
	}	
	else if (hitbox.getType() == OtterEngine::Hitbox::CIRCLE) {
		angle = 2* M_PI * ((float)_angle / 360);
		sf::VertexArray quad(sf::Quads, 4);
		sf::Vector2f circle(hitbox.getPos().x - _pos.x, hitbox.getPos().y - _pos.y);
		quad[3].position = sf::Vector2f(-_squareSize.x / 2, _squareSize.y / 2);
		quad[2].position = sf::Vector2f(_squareSize.x / 2, _squareSize.y / 2);
		quad[1].position = sf::Vector2f(_squareSize.x / 2, -_squareSize.y / 2);
		quad[0].position = sf::Vector2f(-_squareSize.x / 2, -_squareSize.y / 2);
		circle = sf::Vector2f(circle.x * cos(-angle) - circle.y * sin(-angle), circle.x * sin(-angle) + circle.y * cos(-angle));
		if (circle.x >= quad[0].position.x && circle.x <= quad[1].position.x) {
			if (circle.y >= quad[0].position.y && circle.y <=quad[3].position.y)
				return true;
			if (circle.y + hitbox.getRadius() >= quad[0].position.y && circle.y + hitbox.getRadius() <=quad[3].position.y)
				return true;
			if (circle.y - hitbox.getRadius() >= quad[0].position.y && circle.y - hitbox.getRadius() <=quad[3].position.y)
				return true;
			if ((circle.y < quad[0].position.y || circle.y - hitbox.getRadius() < quad[0].position.y) && circle.y + hitbox.getRadius() > quad[3].position.y)
				return true;
			if ((circle.y > quad[3].position.y || circle.y + hitbox.getRadius() > quad[3].position.y) && circle.y - hitbox.getRadius() < quad[0].position.y)
				return true;
		}
		if (circle.y >= quad[0].position.y && circle.y <= quad[3].position.y) {
			if (circle.x <= quad[1].position.x && circle.x >=quad[0].position.x)
				return true;
			if (circle.x + hitbox.getRadius() <= quad[1].position.x && circle.x + hitbox.getRadius() >=quad[0].position.x)
				return true;
			if (circle.x - hitbox.getRadius() <= quad[1].position.x && circle.x - hitbox.getRadius() >=quad[0].position.x)
				return true;
			if ((circle.x > quad[1].position.x || circle.x + hitbox.getRadius() > quad[1].position.x) && circle.x - hitbox.getRadius() < quad[0].position.x) {
				return true;
			}
			if ((circle.x < quad[0].position.x || circle.x - hitbox.getRadius() < quad[0].position.x) && circle.x + hitbox.getRadius() > quad[1].position.x) {
				return true;
			}
		}
		else {
			if (sqrt(pow(quad[0].position.x - circle.x, 2) + pow(quad[0].position.y - circle.y, 2)) <= hitbox.getRadius())
				return true;
			if (sqrt(pow(quad[1].position.x - circle.x, 2) + pow(quad[1].position.y - circle.y, 2)) <= hitbox.getRadius())
				return true;
			if (sqrt(pow(quad[2].position.x - circle.x, 2) + pow(quad[2].position.y - circle.y, 2)) <= hitbox.getRadius())
				return true;
			if (sqrt(pow(quad[3].position.x - circle.x, 2) + pow(quad[3].position.y - circle.y, 2)) <= hitbox.getRadius())
				return true;

		}
		return false;
	}
	
	else {
		angle = 2* M_PI * ((float)hitbox.getAngle() / 360);
		sf::VertexArray quad(sf::Quads, 4);
		sf::Vector2f circle(_pos.x - hitbox.getPos().x, _pos.y - hitbox.getPos().y);
		quad[3].position = sf::Vector2f(-hitbox.getSquareSize().x / 2, hitbox.getSquareSize().y / 2);
		quad[2].position = sf::Vector2f(hitbox.getSquareSize().x / 2, hitbox.getSquareSize().y / 2);
		quad[1].position = sf::Vector2f(hitbox.getSquareSize().x / 2, -hitbox.getSquareSize().y / 2);
		quad[0].position = sf::Vector2f(-hitbox.getSquareSize().x / 2, -hitbox.getSquareSize().y / 2);
		circle = sf::Vector2f(circle.x * cos(-angle) - circle.y * sin(-angle), circle.x * sin(-angle) + circle.y * cos(-angle));
		if (circle.x >= quad[0].position.x && circle.x <= quad[1].position.x) {
			if (circle.y >= quad[0].position.y && circle.y <=quad[3].position.y)
				return true;
			if (circle.y + _radius >= quad[0].position.y && circle.y + _radius <=quad[3].position.y)
				return true;
			if (circle.y - _radius >= quad[0].position.y && circle.y - _radius <=quad[3].position.y)
				return true;
			if ((circle.y < quad[0].position.y || circle.y - _radius < quad[0].position.y) && circle.y + _radius > quad[3].position.y)
				return true;
			if ((circle.y > quad[3].position.y || circle.y + _radius > quad[3].position.y) && circle.y - _radius < quad[0].position.y)
				return true;
		}
	        if (circle.y >= quad[0].position.y && circle.y <= quad[3].position.y) {
			if (circle.x <= quad[1].position.x && circle.x >=quad[0].position.x)
				return true;
			if (circle.x + _radius <= quad[1].position.x && circle.x + _radius >=quad[0].position.x)
				return true;
			if (circle.x - _radius <= quad[1].position.x && circle.x - _radius >=quad[0].position.x)
				return true;
			if ((circle.x > quad[1].position.x || circle.x + _radius > quad[1].position.x) && circle.x - _radius < quad[0].position.x) {
				return true;
			}
			if ((circle.x < quad[0].position.x || circle.x - _radius < quad[0].position.x) && circle.x + _radius > quad[1].position.x) {
				return true;
			}
		}
		else {
			if (sqrt(pow(quad[0].position.x - circle.x, 2) + pow(quad[0].position.y - circle.y, 2)) <= _radius)
				return true;
			if (sqrt(pow(quad[1].position.x - circle.x, 2) + pow(quad[1].position.y - circle.y, 2)) <= _radius)
				return true;
			if (sqrt(pow(quad[2].position.x - circle.x, 2) + pow(quad[2].position.y - circle.y, 2)) <= _radius)
				return true;
			if (sqrt(pow(quad[3].position.x - circle.x, 2) + pow(quad[3].position.y - circle.y, 2)) <= _radius)
				return true;

		}
		return false;
	}
}

void OtterEngine::Hitbox::applyLPos()
{
	_pos = _lpos;
}
