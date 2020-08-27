#pragma once

#include "Object.hpp"
#include "FixedSprite.hpp"

namespace OtterEngine {
	class Gauge : public Object {
	public:
		Gauge(std::string filename, Vector2d pos, int layer,
			Vector2d size, int &data, int min, int max);
		~Gauge();

		void update();

		Vector2d getSize() override;

	private:
		Vector2d _size;

		FixedSprite *_outline;
		FixedSprite *_fill;

		int &_data;
		int _min;
		int _max;
	};
}