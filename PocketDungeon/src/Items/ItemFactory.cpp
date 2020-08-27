//
// Created by flav on 2/14/19.
//

#include "Heart.hpp"
#include "ExpBag.hpp"
#include "Coin.hpp"
#include "CoinBag.hpp"
#include "ItemFactory.hpp"

#define NB_ITEMS 4

ItemFactory::ItemFactory() {}

ItemFactory::~ItemFactory() {}

IItems *ItemFactory::createItem() {
	int r = rand() % NB_ITEMS;

	if (r == 0)
		return new Heart();
	else if (r == 1)
		return new ExpBag();
	else if (r == 2)
		return new CoinBag();
	else
		return new Coin();
}