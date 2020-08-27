#include "MusicManager.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

MusicManager::MusicManager()
{
	
}

MusicManager::~MusicManager()
{

}

bool MusicManager::loadMusicFile(const std::string &filename)
{
	return _music.openFromFile(filename);
}

void MusicManager::play()
{
	_music.play();
}
void MusicManager::pause()
{
	_music.pause();
}

void MusicManager::stop()
{
	_music.stop();
}

void MusicManager::addVolume()
{
	float tmp = _music.getVolume();
	tmp += 3;
	if (tmp > 100)
		tmp = 100;
	_music.setVolume(tmp);
}

void MusicManager::subVolume()
{
	float tmp = _music.getVolume();
	tmp -= 3;
	if (tmp < 0)
		tmp = 0;
	_music.setVolume(tmp);
}

void MusicManager::restart()
{
	_music.setPlayingOffset(sf::Time::Zero);
}
