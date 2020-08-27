//
// Created by flav on 1/10/19.
//

#ifndef POCKETDUNGEON_CAMERA_H
#define POCKETDUNGEON_CAMERA_H


#include <OtterEngine/Object.hpp>
#include "Player.hpp"

class Camera : public virtual OtterEngine::Object {

public:
	Camera(OtterEngine::View *, Player *);
	~Camera();

	bool always(OtterEngine::Engine *);
	int update(OtterEngine::Engine *);

	virtual void updateEvents(OtterEngine::Engine *oe);
protected:
	OtterEngine::View *_view;
	Player *_player;
private:
	std::vector<OtterEngine::Event<Camera>> _events;

};


#endif //POCKETDUNGEON_CAMERA_H
