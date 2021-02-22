#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class Box : public sf::RectangleShape
{
private:
	bool state;
	sf::Sound boxSound;

public:
	Box(sf::Vector2f size);
	void setSound(sf::SoundBuffer& sound);
	void playSound();
	void setState(bool state);
	bool isActive();
	void draw(sf::RenderWindow* window);
};