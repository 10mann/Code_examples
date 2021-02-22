#include "TextField.h"


// ========================== Constructors ==========================
TextField::TextField()
	: active(false), defaultColor(sf::Color::White), hoverColor(sf::Color(200, 200, 200)), activeColor(sf::Color(54, 184, 217, 100)), maxDigitSize(4)
{

}

TextField::~TextField()
{

}


// ========================== Accessors ==========================
const bool& TextField::isPressed(const sf::Vector2f& mousePos)
{
	this->active = this->getGlobalBounds().contains(mousePos);
	if (this->active)
	{
		this->inputText = "";
	}
	return this->active;
}

const unsigned short& TextField::getInputValue()
{
	if (this->inputText.empty())
		return 0;

	return std::stoi(this->inputText);
}


// ========================== Functions ==========================
void TextField::create(sf::Vector2f pos, sf::Vector2f size, sf::Font& font)
{
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(20);

	this->setPosition(pos);
	this->setSize(size);
	this->setFillColor(sf::Color::White);
	this->setOutlineThickness(1.0f);
	this->setOutlineColor(sf::Color::Black);

	inputText.reserve(this->maxDigitSize);

	//std::cout << "Textfield created at (" << this->getPosition().x << ", " << this->getPosition().y << ")\n";
}

void TextField::update(const sf::Vector2f& mousePos)
{
	if (this->active)
	{
		this->setFillColor(this->activeColor);
	}
	else if (this->getGlobalBounds().contains(mousePos))
	{
		this->setFillColor(this->hoverColor);
	}
	else
	{
		this->setFillColor(this->defaultColor);
	}
}

void TextField::updateText(sf::Uint32 input)
{
	if (input == 8 && this->inputText.size() > 0)
	{
		//this->inputText[this->inputText.size() - 1] = '\0';
		this->inputText.resize(this->inputText.size() - 1);

	}
	else if (input > 48 && input < 58)
	{
		this->inputText += input;

		if (this->inputText.size() > this->maxDigitSize)
		{
			this->inputText.resize(this->maxDigitSize);
		}
	}

	this->text.setString(this->inputText);
	sf::Vector2f textPos((int)(this->getPosition().x + this->getSize().x - this->text.getGlobalBounds().width - 5.0f), (int)(this->getPosition().y + this->getSize().y / 2.0f - this->text.getCharacterSize() / 1.8f));
	this->text.setPosition(textPos);
}

void TextField::render(sf::RenderWindow* window)
{
	window->draw(*this);
	window->draw(this->text);
}

