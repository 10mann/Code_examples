#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"


class StateButton
{
private:
	// Variables
	sf::RectangleShape box;
	sf::Text text;
	sf::Color defaultColor;
	sf::Color activeColor;
	bool active;

	// Init functions

public:
	// ========================== Constructors ==========================
	StateButton(sf::Vector2f pos, sf::Vector2f size, std::string buttonText, sf::Font& font, sf::Color defaultColor = sf::Color(100, 100, 100, 100), sf::Color hoverColor = sf::Color(100, 100, 100), sf::Color activeColor = sf::Color(0, 255, 0));
	virtual ~StateButton();


	// ========================== Accessors ==========================
	const bool& isActive();


	// ========================== Functions ==========================
	const bool isPressed(const sf::Vector2f& mousePos);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderWindow* window);
};

