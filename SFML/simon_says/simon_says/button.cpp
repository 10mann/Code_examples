#include "button.h"


// ================ Constructors ================
Button::Button()
{
	this->pos = sf::Vector2f(0, 0);
	this->size = sf::Vector2f(0, 0);
	this->index = -1;
}

// Creates a button at desired position with given size, index and texture
Button::Button(sf::Vector2f pos, sf::Vector2f size, int index, sf::Texture& pressedTexture, sf::Texture& notPressedTexture)
{
	this->pos = pos;
	this->size = size;
	this->index = index;
	this->pressed = false;
	this->pressedTexture = pressedTexture;
	this->notPressedTexture = notPressedTexture;
	this->textureSize = sf::Vector2f(pressedTexture.getSize().x, pressedTexture.getSize().y);
	this->buttonTexture.setTexture(this->notPressedTexture);
	sf::Vector2f scale = sf::Vector2f(this->size.x / this->textureSize.x, this->size.y / this->textureSize.y);
	this->buttonTexture.setScale(scale);
	this->buttonTexture.setPosition(this->pos);
}

// ================ Functions ================
void Button::setPos(sf::Vector2f newPos)
{
	this->pos = newPos;
	this->buttonTexture.setPosition(newPos);
}

// Sets the size of the button
void Button::setSize(sf::Vector2f newSize)
{
	sf::Vector2f scale = sf::Vector2f(newSize.x / this->textureSize.x, newSize.y / this->textureSize.y);
	this->size = newSize;
	this->buttonTexture.setScale(scale);
}

// Sets the texture of the button
void Button::setTexture(sf::Texture& texture)
{
	this->buttonTexture.setTexture(texture);
}

// Sets the sound of the button
void Button::setSound(sf::SoundBuffer& sound)
{
	this->sound.setBuffer(sound);
}

// Draws the button to the screen
void Button::draw(sf::RenderWindow* window)
{
	window->draw(this->buttonTexture);
}

// Checks if the cursor is within the button boundaries
bool Button::isMouseOver(sf::Vector2i mouse)
{
	return (mouse.x > this->pos.x && mouse.x < this->pos.x + this->size.x && mouse.y > this->pos.y && mouse.y < this->pos.y + this->size.y);
}

// Returns the index of the button
int Button::getIndex()
{
	return this->index;
}

// Changes texture of the button and plays the button sound
void Button::press()
{
	this->pressed = true;
	this->buttonTexture.setTexture(this->pressedTexture);
	
	if (this->sound.getBuffer() != nullptr)
	{
		this->sound.play();
	}
	else
	{
		printf("No sound to play\n");
	}
	
}

// Changes the texture back to unpressed
void Button::release()
{
	this->pressed = false;
	this->buttonTexture.setTexture(this->notPressedTexture);
}