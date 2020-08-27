//
// Created by flav on 1/31/19.
//

#ifndef POCKETDUNGEON_IITEMS_H
#define POCKETDUNGEON_IITEMS_H


#include <OtterEngine/Object.hpp>

class IItems : virtual public OtterEngine::Object {
public:
	IItems();
	~IItems();

protected:
	float _launchTime;
};


#endif //POCKETDUNGEON_IITEMS_H
