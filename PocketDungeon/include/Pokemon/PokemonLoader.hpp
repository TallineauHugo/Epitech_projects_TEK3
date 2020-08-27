//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// pokemon loader
//

#pragma once

#include <map>
#include <vector>
#include "Pokemon.hpp"

#define PKMN_FILES_PATH "ressources/pokemons/"
#define FILE_EXTENSION ".pkmn"
#define STAT_DELIM ':'

class PokemonLoader
{
public:
	static PokemonLoader *getInstance() {
		static PokemonLoader instance;

		return &instance;
	}
	~PokemonLoader();
public:	
	Pokemon *getPokemonById(int id) const;
	Pokemon *getPokemonByName(std::string name) const;
private:
	PokemonLoader();
	bool loadPokemons();
	bool loadPokemon(std::string name);
	
	std::string getFilePath(std::string pkmnName);
	
private:
	std::map<int, Pokemon*> _mIdToPkmn;
	std::map<std::string, int> _mNameToId;
};
