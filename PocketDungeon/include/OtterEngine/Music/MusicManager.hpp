#include <SFML/Audio.hpp>

class MusicManager
{
public:
	MusicManager();
	~MusicManager();

	bool loadMusicFile(const std::string &filename);
	void play();
	void pause();
	void stop();
	void addVolume();
	void subVolume();
	void restart();
	
private:
	sf::Music _music;
	
};
