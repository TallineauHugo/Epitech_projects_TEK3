#pragma once

#include "Object.hpp"
#include "FixedSprite.hpp"

namespace OtterEngine {
	class Gauge : public Object {
	public:
		Gauge(std::string outline, std::string fill, Vector2d pos, int layer,
			Vector2d size, int& data, int min, int& max);
		~Gauge();

		void update();
		void show();
		void hide();

		Vector2d getSize() override;

	private:
		Vector2d _size;

		FixedSprite *_outline;
		FixedSprite *_fill;

		int& _data;
		int _min;
		int& _max;
		int _layer;
	};
}
