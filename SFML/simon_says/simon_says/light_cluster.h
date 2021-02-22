#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "light.h"

class LightCluster
{
private:
	sf::Vector2f pos;
	int width;
	sf::RenderWindow* window;
	sf::Texture lightOnTexture;
	sf::Texture lightOffTexture;
	std::vector<Light> lights;
	sf::SoundBuffer sound;
	int numberOfLights;
	int lightSize;
	int activeLights;

public:
	// ================ Constructors ================
	LightCluster(sf::RenderWindow* window);

	// ================ Functions ================
	bool createDefaultCluster(sf::Vector2f pos, int width, int difficulty);
	void setActive(int num);
	void draw();
};