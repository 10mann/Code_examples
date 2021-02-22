#pragma once

#include <vector>
#include <thread>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "button.h"


class ButtonPanel
{
private:
	const int numberOfButtons = 9;
	Button* pressedButton;
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::RenderWindow* window;
	sf::Texture buttonPressedTexture;
	sf::Texture buttonNotPressedTexture;
	std::vector<Button> buttons;
	std::vector<sf::SoundBuffer> sounds;
	int buttonSize;
	sf::Vector2f btnSize;
	sf::Vector2f buttonGrid;
	bool started = false;
	int pressedButtonIndex;

	sf::RectangleShape box;

public:
	// ================ Constructors ================
	ButtonPanel(sf::RenderWindow* window);
	~ButtonPanel();

	// ================ Functions ================
	bool createDefaultGrid(sf::Vector2f pos, sf::Vector2f size);
	bool createButtonGrid(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f buttonGrid);
	bool setButtonSounds(std::vector<sf::SoundBuffer>& sounds);
	void setButtonTexture(sf::Texture& texture);
	bool mouseOver(sf::Vector2i mosue);
	bool pressed(sf::Vector2i mouse);
	int getButtonPressedIndex();
	void setNotPressed();
	void resetButton();
	void draw();
};