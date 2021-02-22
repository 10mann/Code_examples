#include "button_sounds.h"

// Used to init button sounds
// Reads the audio files from disk
bool initInputButtonSounds(std::vector<sf::SoundBuffer>& sounds)
{
	sf::SoundBuffer sound;

	int numberOfButtons = 9;

	sf::SoundBuffer buttonSound;
	for (int i = 0; i < numberOfButtons; i++)
	{
		char fileName[25];
		snprintf(fileName, 25, "Lyder/button_%i_press.wav", i);
		if (!buttonSound.loadFromFile(fileName))
		{
			return false;
			//printf("Couldn't load button %i sound\n", i);
		}
		else
		{
			sounds.push_back(buttonSound);
			//printf("%s loaded\n", fileName);
		}
	}

	return true;
}

