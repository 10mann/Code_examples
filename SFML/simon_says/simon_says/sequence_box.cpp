#include "sequence_box.h"


// ================ Constructors ================
Box::Box(sf::Vector2f size)
{
	this->state = false;
	this->setSize(size);
}

// ================ Functions ================

// Sets the sound of the cell
void Box::setSound(sf::SoundBuffer& sound)
{
	this->boxSound.setBuffer(sound);
}

// Plays the cell sound
void Box::playSound()
{
	if (this->boxSound.getBuffer() != nullptr)
		this->boxSound.play();
}

// Sets the desired state of the cell
void Box::setState(bool state)
{
	if (state && !this->state)
	{
		if(this->boxSound.getBuffer() != nullptr)
			this->boxSound.play();
	}

	this->state = state;
}

// Checks if cell is active
bool Box::isActive()
{
	return this->state;
}

// Draws the cell to the screen
void Box::draw(sf::RenderWindow* window)
{
	window->draw(*this);
}