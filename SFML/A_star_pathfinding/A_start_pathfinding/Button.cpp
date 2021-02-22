#include "Button.h"


// ========================== Constructors ==========================
Button::Button(sf::Vector2f pos, sf::Vector2f size, std::string buttonText, sf::Font& font, sf::Color defaultColor, sf::Color hoverColor, sf::Color activeColor, const unsigned short index)
	: defaultColor(defaultColor), hoverColor(hoverColor), activeColor(activeColor), index(index)
{
	this->box.setPosition(pos);
	this->box.setSize(size);
	this->box.setOutlineThickness(1.0f);
	this->box.setOutlineColor(sf::Color::Black);
	this->box.setFillColor(this->defaultColor);

	this->text.setFont(font);
	this->text.setString(buttonText);
	this->text.setCharacterSize(22);
	this->text.setFillColor(sf::Color::Black);
	this->text.setPosition(this->box.getPosition() + sf::Vector2f(static_cast<int>((this->box.getSize().x - this->text.getGlobalBounds().width) / 2.0f), static_cast<int>(this->box.getSize().y / 2.0f - this->text.getCharacterSize() / 1.8f)));
}

Button::~Button()
{
}


// ========================== Accessors ==========================
const std::string Button::getString()
{
	return std::string(this->text.getString());
}

void Button::setString(const std::string buttonText)
{
	this->text.setString(buttonText);
}

const unsigned short& Button::getIndex()
{
	return this->index;
}

void Button::setIndex(const unsigned short index)
{
	this->index = index;
}


// ========================== Functions ==========================
const bool Button::isPressed(const sf::Vector2f& mousePos)
{
	return this->box.getGlobalBounds().contains(mousePos);;
}


void Button::update(const sf::Vector2f& mousePos)
{
	if (this->box.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->box.setFillColor(activeColor);
		}
		else
		{
			this->box.setFillColor(this->hoverColor);
		}
	}
	else
	{
		this->box.setFillColor(this->defaultColor);
	}
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(this->box);
	window->draw(this->text);
}
