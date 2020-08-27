#pragma once

#include "Object.hpp"

namespace OtterEngine {
	class Circle : public virtual Object {
	public:
		Circle(Vector2d pos, int radius);
		~Circle();
		virtual void updateEvents(OtterEngine::Engine *);

	private:
		std::vector<OtterEngine::Event<Circle>> _events;
	};
}