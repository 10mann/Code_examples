#pragma once

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"


class TextField : public sf::RectangleShape
{
private:
	// Variables
	bool active;
	sf::Color defaultColor;
	sf::Color hoverColor;
	sf::Color activeColor;
	sf::Text text;
	std::string inputText;
	const unsigned short maxDigitSize;

public:
	// ========================== Constructors ==========================
	TextField();
	virtual ~TextField();

	// ========================== Accessors ==========================
	const bool& isPressed(const sf::Vector2f& mousePos);
	const unsigned short& getInputValue();

	// ========================== Functions ==========================
	void create(sf::Vector2f pos, sf::Vector2f size, sf::Font& font);
	void update(const sf::Vector2f& mousePos);
	void updateText(sf::Uint32 input);
	void render(sf::RenderWindow* window);


};

