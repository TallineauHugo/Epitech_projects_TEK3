//
// Created by flav on 1/31/19.
//

#ifndef POCKETDUNGEON_HEART_H
#define POCKETDUNGEON_HEART_H


#include "IItems.hpp"

class Heart : public virtual IItems {
public:
	Heart();
	~Heart();
	bool TimeVerification(OtterEngine::Engine *oe);
	int TimeReaction(OtterEngine::Engine *oe);
	bool collideVerification(OtterEngine::Engine *oe);
	int collideReaction(OtterEngine::Engine *oe);


	void updateEvents(OtterEngine::Engine *oe);

private:
	std::vector<OtterEngine::Event<Heart>> _events;
};


#endif //POCKETDUNGEON_HEART_H
