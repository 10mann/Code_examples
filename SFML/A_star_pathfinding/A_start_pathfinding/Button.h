#pragma once

#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"


class Button
{
private:

protected:
	// Variables
	sf::RectangleShape box;
	sf::Text text;
	sf::Color defaultColor;
	sf::Color hoverColor;
	sf::Color activeColor;

	unsigned short index;


public:
	//  ========================== Constructors ==========================
	Button(sf::Vector2f pos, sf::Vector2f size, std::string buttonText, sf::Font& font, sf::Color defaultColor = sf::Color(100, 100, 100, 100), sf::Color hoverColor = sf::Color(100, 100, 100), sf::Color activeColor = sf::Color(100, 100, 100, 100), const unsigned short index = 0);
	virtual ~Button();

	// ========================== Accessors ==========================
	const std::string getString();
	void setString(const std::string buttonText);
	const unsigned short& getIndex();
	void setIndex(const unsigned short index);

	// ========================== Functions ==========================
	const bool isPressed(const sf::Vector2f& mousePos);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderWindow* window);
};

