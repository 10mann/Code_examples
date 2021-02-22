#include "light.h"


// ================ Constructors ================

// Creates a light with a given position, size, texture and sound
Light::Light(sf::Vector2f pos, int size, sf::Texture& lightOnTexture, sf::Texture& lightOffTexture, sf::SoundBuffer& sound)
{
	this->pos = pos;
	this->size = size;
	this->lightOnTexture = lightOnTexture;
	this->lightOffTexture = lightOffTexture;
	this->texture.setTexture(this->lightOffTexture);
	sf::Vector2f scale = sf::Vector2f((float)this->size / (float)this->lightOffTexture.getSize().x, (float)this->size / (float)this->lightOffTexture.getSize().y);
	this->texture.setScale(scale);
	this->texture.setPosition(this->pos);
	this->sound.setBuffer(sound);
	this->sound.setVolume(10.0f);
}

// ================ Functions ================

// Sets the state of the light and plays sound if the light is turned on
void Light::setActive(bool state)
{
	this->on = state;
	if (state)
	{
		this->texture.setTexture(this->lightOnTexture);
		if (this->sound.getBuffer() != nullptr)
		{
			this->sound.play();
		}
	}
	else
	{
		this->texture.setTexture(this->lightOffTexture);
	}
}

// Sets the texture of the light
void Light::setTexture(sf::Texture& texture)
{
	this->texture.setTexture(texture);
}

// Returns the state of the light
bool Light::getState()
{
	return this->on;
}

// Draws the light to the screen
void Light::draw(sf::RenderWindow* window)
{
	window->draw(this->texture);
}