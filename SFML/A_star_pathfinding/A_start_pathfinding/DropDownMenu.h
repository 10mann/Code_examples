#pragma once

#include <vector>

#include "Button.h"


class DropDownMenu
{
private:
	// ========================== Variables ==========================
	sf::RenderWindow* window;
	sf::Vector2f position;
	sf::Vector2f size;

	unsigned short numberOfElements;
	std::shared_ptr<Button> activeElement;
	std::vector<std::shared_ptr<Button>> buttons;

	bool showList;

public:
	// ========================== Constructors ==========================
	DropDownMenu();
	virtual ~DropDownMenu();

	// ========================== Accessors ==========================
	const std::string getActiveElementText();
	const unsigned short getActiveElementIndex();
	const bool isPressed(const sf::Vector2f& mousePos);

	// ========================== Functions ==========================
	void create(sf::RenderWindow* window, sf::Vector2f pos, sf::Vector2f size, std::vector<std::string>& textList, sf::Font& font, unsigned short numberOfElements, unsigned short defaultElement = 0);
	void update(const sf::Vector2f& mousePos);
	void render();
};

