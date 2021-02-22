#include "button_panel.h"


// ================ Constructors ================
ButtonPanel::ButtonPanel(sf::RenderWindow* window)
{
	this->pos = sf::Vector2f(0, 0);
	this->window = window;
	this->buttonGrid = sf::Vector2f(0, 0);
	this->buttons.clear();
	this->pressedButton = nullptr;
	this->buttonSize = 0;
	this->pressedButtonIndex = -1;
}

ButtonPanel::~ButtonPanel()
{

}

// ================ Functions ================

// Used to create a default grid at position with a given size
bool ButtonPanel::createDefaultGrid(sf::Vector2f pos, sf::Vector2f size)
{
	this->pos = pos;
	this->size = size;
	this->buttonGrid = sf::Vector2f(3, 3);
	this->buttons.clear();
	this->sounds.clear();

	this->box = sf::RectangleShape(this->size);
	this->box.setPosition(this->pos);
	this->box.setFillColor(sf::Color(200, 200, 200));
	this->box.setOutlineThickness(2);
	this->box.setOutlineColor(sf::Color(0, 0, 0));

	float spaceFactor = 20.0;
	int buttonSpace = this->size.x / spaceFactor;

	this->btnSize.x = (this->size.x - buttonSpace * (this->buttonGrid.x + 1)) / this->buttonGrid.x;
	this->btnSize.y = (this->size.y - buttonSpace * (this->buttonGrid.y + 1)) / this->buttonGrid.y;
	int numberOfButtons = this->buttonGrid.x * this->buttonGrid.y;

	//printf("Button size: (%f, %f)\n", this->btnSize.x, this->btnSize.y);

	if (!this->buttonPressedTexture.loadFromFile("Bilder/button_pressed.png"))
	{
		//printf("Couldn't load button on image\n");
		return false;
	}
	if (!this->buttonNotPressedTexture.loadFromFile("Bilder/button.png"))
	{
		//printf("Couldn't load button off image\n");
		return false;
	}


	for (int i = 0; i < this->buttonGrid.y; i++)
	{
		for (int j = 0; j < this->buttonGrid.x; j++)
		{
			sf::Vector2f buttonPos = this->pos + sf::Vector2f(j * (this->btnSize.x + buttonSpace) + buttonSpace, i * (this->btnSize.y + buttonSpace) + buttonSpace);
			this->buttons.push_back(Button(buttonPos, this->btnSize, i * this->buttonGrid.y + j, this->buttonPressedTexture, this->buttonNotPressedTexture));
			this->buttons[i * this->buttonGrid.y + j].setTexture(this->buttonNotPressedTexture);
		}
	}

	return true;
}

// Used to create a button grid at a position with a given size
bool ButtonPanel::createButtonGrid(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f buttonGrid)
{
	if (!this->buttonPressedTexture.loadFromFile("Bilder/button_pressed.png"))
	{
		//printf("Couldn't load button on image\n");
		return false;
	}
	if (!this->buttonNotPressedTexture.loadFromFile("Bilder/button.png"))
	{
		//printf("Couldn't load button off image\n");
		return false;
	}

	this->pos = pos;
	this->size = size;
	this->buttonGrid = buttonGrid;
	this->buttons.clear();

	this->box = sf::RectangleShape(this->size);
	this->box.setPosition(this->pos);
	this->box.setFillColor(sf::Color(200, 200, 200));
	this->box.setOutlineThickness(2);
	this->box.setOutlineColor(sf::Color(0, 0, 0));

	float spaceFactor = 20.0;
	int buttonSpace = this->size.x / spaceFactor;

	this->btnSize.x = (this->size.x - buttonSpace * (this->buttonGrid.x + 1)) / this->buttonGrid.x;
	this->btnSize.y = (this->size.y - buttonSpace * (this->buttonGrid.y + 1)) / this->buttonGrid.y;
	int numberOfButtons = this->buttonGrid.x * this->buttonGrid.y;

	for (int i = 0; i < this->buttonGrid.y; i++)
	{
		for (int j = 0; j < this->buttonGrid.x; j++)
		{
			sf::Vector2f buttonPos = this->pos + sf::Vector2f(j * (this->btnSize.x + buttonSpace) + buttonSpace, i * (this->btnSize.y + buttonSpace) + buttonSpace);
			this->buttons.push_back(Button(buttonPos, this->btnSize, i * this->buttonGrid.y + j, this->buttonPressedTexture, this->buttonNotPressedTexture));
			this->buttons[i * this->buttonGrid.y + j].setTexture(this->buttonNotPressedTexture);
		}
	}

	return true;
}

// Sets the sound that should be played when a button is pressed
bool ButtonPanel::setButtonSounds(std::vector<sf::SoundBuffer>& sounds)
{
	int numberOfSounds = sounds.size();
	int numberOfButtons = this->buttons.size();

	if (numberOfSounds != numberOfButtons)
	{
		return false;
	}

	for (int i = 0; i < numberOfButtons; i++)
	{
		this->buttons[i].setSound(sounds[i]);
	}
}

// Sets desired texture of buttons
void ButtonPanel::setButtonTexture(sf::Texture& texture)
{
	for (auto& button : this->buttons)
	{
		button.setTexture(texture);
	}
}

// Checks if the cursor is inside the grid
bool ButtonPanel::mouseOver(sf::Vector2i mouse)
{
	return (mouse.x > this->pos.x && mouse.x < this->pos.x + this->size.x && mouse.y > this->pos.y && mouse.y < this->pos.y + this->size.y);
}

// Returns true if a button was pressed inside the grid
bool ButtonPanel::pressed(sf::Vector2i mouse)
{
	if (!this->mouseOver(mouse))
		return false;

	for (int i = 0; i < this->buttons.size(); i++)
	{
		if (this->buttons[i].isMouseOver(mouse))
		{
			this->buttons[i].press();
			this->pressedButton = &this->buttons[i];
			this->pressedButtonIndex = this->buttons[i].getIndex();
			return true;
		}
	}

	return false;
}

// Returns the index of the latest pressed button, returns -1 if no button was pressed
int ButtonPanel::getButtonPressedIndex()
{
	int buttonPressed = this->pressedButtonIndex;
	this->pressedButtonIndex = -1;
	return buttonPressed;
}

void ButtonPanel::setNotPressed()
{
	this->setButtonTexture(this->buttonNotPressedTexture);
}

// Resets pressed button
void ButtonPanel::resetButton()
{
	this->pressedButtonIndex = -1;

	if (this->pressedButton != nullptr)
	{
		this->pressedButton->release();
	}

	this->pressedButton = nullptr;
}

// Draws the button grid to the screen
void ButtonPanel::draw()
{
	this->window->draw(this->box);
	for (auto& button : this->buttons)
	{
		button.draw(this->window);
	}
}
