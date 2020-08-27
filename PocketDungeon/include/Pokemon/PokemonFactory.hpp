//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// pokemon factory
//

#pragma once

#include <memory>

class Pokemon;

class PokemonFactory
{
public:
	static PokemonFactory *getInstance() {
		static PokemonFactory instance;

		return &instance;
	}
	~PokemonFactory();

	Pokemon *createPokemon(std::string pokemon, std::size_t lvl);
private:
	PokemonFactory();
};
