#pragma once

#include "Object.hpp"
#include "define.hpp"

class ScrollingCamera : public virtual OtterEngine::Object
{
public:
	ScrollingCamera(OtterEngine::View *);
	~ScrollingCamera();

	bool always(OtterEngine::Engine *);
	int update(OtterEngine::Engine *);

	virtual void updateEvents(OtterEngine::Engine *oe);
	
protected:
	OtterEngine::View *_view;
private:
	std::vector<OtterEngine::Event<ScrollingCamera>> _events;
};
