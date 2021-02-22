#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Button
{
private:
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Vector2f textureSize;
	int index;
	bool pressed = false;
	sf::Texture pressedTexture;
	sf::Texture notPressedTexture;
	sf::Sprite buttonTexture;
	sf::Sound sound;

public:
	Button();
	Button(sf::Vector2f pos, sf::Vector2f size, int index, sf::Texture& pressedTexture, sf::Texture& notPressedTexture);

	void setSize(sf::Vector2f size);
	void setPos(sf::Vector2f pos);
	void setTexture(sf::Texture& texture);
	void setSound(sf::SoundBuffer& sound);
	void draw(sf::RenderWindow* window);
	bool isMouseOver(sf::Vector2i mouse);
	int getIndex();
	void press();
	void release();
};