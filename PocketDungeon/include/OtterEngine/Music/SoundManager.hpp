#include <SFML/Audio.hpp>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	bool addSound(const std::string &filename);
	void refresh();
	void pauseSounds();
	void resumeSounds();
	void stopSounds();
private:
	std::vector<sf::Music *> _sounds;
};
