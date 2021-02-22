#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class Light
{
private:
	int size;
	sf::Vector2f pos;
	bool on = false;
	sf::CircleShape circle;
	sf::Texture lightOnTexture;
	sf::Texture lightOffTexture;
	sf::Sprite texture;
	sf::Sound sound;
	

public:
	// ================ Constructors ================
	Light(sf::Vector2f pos, int size, sf::Texture& lightOnTexture, sf::Texture& lightOffTexture, sf::SoundBuffer& sound);

	// ================ Functions ================
	void setActive(bool state);
	void setTexture(sf::Texture& texture);
	bool getState();

	void draw(sf::RenderWindow* window);
};