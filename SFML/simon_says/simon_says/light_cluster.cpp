#include "light_cluster.h"


// ================ Constructors ================

// Creates a light cluster with a pointer to the window
LightCluster::LightCluster(sf::RenderWindow* window)
{
	this->pos = pos;
	this->width = 0;
	this->window = window;
	this->numberOfLights = 0;
	this->lights.clear();
	this->activeLights = 0;
	this->lightSize = 0;
	//printf("Created light cluster at (%f, %f)\n", this->pos.x, this->pos.y);
}

// ================ Functions ================

// Creates a light cluster with default parameters with a given size, position and difficulty
bool LightCluster::createDefaultCluster(sf::Vector2f pos, int width, int difficulty)
{
	this->pos = pos;
	this->numberOfLights = difficulty;
	this->width = width;
	float spaceFactor = 20.0f;
	int lightSpace = width / spaceFactor;
	this->lightSize = (this->width - lightSpace * (this->numberOfLights - 1)) / this->numberOfLights;
	this->lights.clear();

	if (!this->sound.loadFromFile("Lyder/light_on.wav"))
	{
		return false;
	}

	if (!this->lightOnTexture.loadFromFile("Bilder/light_on.png"))
	{
		return false;
	}
	if (!this->lightOffTexture.loadFromFile("Bilder/light_off.png"))
	{
		return false;
	}

	this->lightOffTexture.setSmooth(true);
	this->lightOnTexture.setSmooth(true);

	int horizontalSpace = this->lightSize + lightSpace;

	for (int i = 0; i < this->numberOfLights; i++)
	{
		sf::Vector2f lightPos = this->pos + sf::Vector2f(horizontalSpace * i, 0);

		this->lights.push_back(Light(lightPos, this->lightSize, this->lightOnTexture, this->lightOffTexture, this->sound));
		this->lights[i].setTexture(this->lightOffTexture);
	}

	return true;
}

// Sets number of active lights
void LightCluster::setActive(int num)
{
	if (num < 0)
	{
		return;
	}

	if (num > this->lights.size())
	{
		num = this->lights.size();
	}

	if (num > this->activeLights)
	{
		for (int i = this->activeLights; i < num; i++)
		{
			this->lights[i].setActive(true);
		}
	}

	else
	{
		for (int i = num; i < this->lights.size(); i++)
		{
			this->lights[i].setActive(false);
		}
	}

	this->activeLights = num;
}

// Draws the lights to the screen
void LightCluster::draw()
{
	for (auto& light : this->lights)
	{
		light.draw(this->window);
	}
}