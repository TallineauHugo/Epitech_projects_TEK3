//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// pokemon factory
//

#include "PokemonFactory.hpp"
#include "PokemonLoader.hpp"

PokemonFactory::PokemonFactory()
{}

PokemonFactory::~PokemonFactory()
{}
#include <iostream>
Pokemon *PokemonFactory::createPokemon(std::string pokemon, std::size_t lvl)
{
	Pokemon *pkmn = PokemonLoader::getInstance()->getPokemonByName(pokemon);
	if (!pkmn)
		return nullptr;

	Pokemon *ret = new Pokemon(pkmn);

	if (pkmn && ret)
		ret->setLvl(lvl);
	return ret;
}
