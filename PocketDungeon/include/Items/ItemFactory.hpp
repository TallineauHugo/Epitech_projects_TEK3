//
// Created by flav on 2/14/19.
//

#ifndef POCKETDUNGEON_ITEMFACTORY_H
#define POCKETDUNGEON_ITEMFACTORY_H


#include <Items/IItems.hpp>

class ItemFactory {
public:
	ItemFactory();
	~ItemFactory();
	IItems *createItem();
};


#endif //POCKETDUNGEON_ITEMFACTORY_H
