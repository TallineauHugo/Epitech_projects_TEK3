#include "SoundManager.hpp"

SoundManager::SoundManager()
{
	
}

SoundManager::~SoundManager()
{

}

bool SoundManager::addSound(const std::string &filename)
{
	_sounds.insert(_sounds.begin(), new sf::Music);
	if (!_sounds[0]->openFromFile(filename))
		return false;
	_sounds[0]->play();
	return true;
}

void SoundManager::refresh()
{
	for (std::size_t i = 0; i < _sounds.size(); i++)	{
		if (_sounds[i]->getStatus() == sf::SoundSource::Status::Stopped) {
			_sounds.erase(_sounds.begin()+i);
			i--;
		}
	}
}

void SoundManager::pauseSounds()
{
	for (std::size_t i = 0; i < _sounds.size(); i++) {
		_sounds[i]->pause();
	}
}

void SoundManager::resumeSounds()
{
	for (std::size_t i = 0; i < _sounds.size(); i++) {
		_sounds[i]->play();
	}
}

void SoundManager::stopSounds()
{
	while (_sounds.size() > 0) {
		_sounds[0]->stop();
		_sounds.erase(_sounds.begin());
	}
}
