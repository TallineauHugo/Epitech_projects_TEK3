//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// pokemon loader
//

#include <iostream>
#include <utility>
#include "PokemonLoader.hpp"
#include "Parser.hpp"

bool PokemonLoader::loadPokemons()
{
	std::string buff;
	std::vector<std::string> vPokemons;
	std::size_t size = 0;
	Parser *parser = Parser::getInstance();
	
	if (!parser->readFileByName(this->getFilePath("list"), buff))
		return false;
	vPokemons = parser->splitStringToVector(buff, '\n');
	size = vPokemons.size();
	std::cout << "nb pokémons à load: " << size << std::endl;

	for (std::size_t i = 0; i < size; i++) {
		std::cout << "Loading " << vPokemons[i] << " ... \t";
		std::cout << ((this->loadPokemon(vPokemons[i])) ? ("SUCESS") : ("FAILURE")) << std::endl;
	}

	return true;
}

Pokemon *PokemonLoader::getPokemonById(int id) const
{
	if (_mIdToPkmn.find(id) == _mIdToPkmn.end())
		return nullptr;
	return _mIdToPkmn.at(id);
}

Pokemon *PokemonLoader::getPokemonByName(std::string name) const
{
	if (_mNameToId.find(name) == _mNameToId.end())
		return nullptr;
	return _mIdToPkmn.at(_mNameToId.at(name));
}

//public
//--------------------------------------------------------------
//private

bool PokemonLoader::loadPokemon(std::string name)
{
	std::string file;
	std::vector<std::string> vTokens;
	std::pair<std::string, std::string> stat;
	std::size_t id;
	std::size_t i = 0;
	std::size_t size = 0;
	Pokemon* pkmn = nullptr;
	Parser *parser = Parser::getInstance();

	if (!parser->readFileByName(this->getFilePath(name), file))
		return false;
	
	vTokens = parser->splitStringToVector(file, '\n');
	size = vTokens.size();
	pkmn = new Pokemon(name);
	while (i != size) {
		stat = parser->splitStringToPair(vTokens[i], STAT_DELIM);
		pkmn->setBaseStat(stat);
		i++;
	}
	id = pkmn->getId();
	_mNameToId[name] = id;
	_mIdToPkmn[id] = pkmn;
	pkmn->setLvl(1);
	return true;
}

std::string PokemonLoader::getFilePath(std::string pkmnName)
{
	std::string filename(PKMN_FILES_PATH);

	filename += pkmnName;
	filename += FILE_EXTENSION;

	return filename;
}

PokemonLoader::PokemonLoader()
{
	loadPokemons();
}

PokemonLoader::~PokemonLoader()
{
	std::map<int, Pokemon*>::iterator it = _mIdToPkmn.begin();

	while (it != _mIdToPkmn.end()) {
		delete it->second;
		it++;
	}
}
