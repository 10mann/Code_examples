#include "DropDownMenu.h"

// ========================== Constructors ==========================
DropDownMenu::DropDownMenu()
	: window(nullptr), position(sf::Vector2f(0, 0)), size(sf::Vector2f(0, 0)), numberOfElements(0)
{

}

DropDownMenu::~DropDownMenu()
{

}


// ========================== Accessors ==========================
const std::string DropDownMenu::getActiveElementText()
{
	return this->activeElement->getString();
}

const unsigned short DropDownMenu::getActiveElementIndex()
{
	return this->activeElement->getIndex();
}

const bool DropDownMenu::isPressed(const sf::Vector2f& mousePos)
{

	if (this->activeElement->isPressed(mousePos))
	{
		this->showList = !this->showList;
		return true;
	}

	if (this->showList)
	{
		for (auto& button : this->buttons)
		{
			if (button->isPressed(mousePos))
			{
				this->activeElement->setString(button->getString());
				this->activeElement->setIndex(button->getIndex());
				this->showList = false;
				return true;
			}
		}
	}

	return false;
}


// ========================== Functions ==========================
void DropDownMenu::create(sf::RenderWindow* window, sf::Vector2f pos, sf::Vector2f size, std::vector<std::string>& textList, sf::Font& font, unsigned short numberOfElements, unsigned short defaultElement)
{
	this->window = window;
	this->position = pos;
	this->size = size;
	this->numberOfElements = numberOfElements;
	this->activeElement = std::make_shared<Button>(this->position, this->size, textList[defaultElement], font, sf::Color(255, 255, 255, 150), sf::Color(200, 200, 200), sf::Color(255, 255, 255, 150));

	this->buttons.reserve(this->numberOfElements);

	for (size_t i = 0; i < this->numberOfElements; ++i)
	{
		this->buttons.push_back(std::make_shared<Button>(this->position + sf::Vector2f(0, (i + 1) * (this->size.y + 1)), this->size, textList[i], font, sf::Color(255, 255, 255, 150), sf::Color(200, 200, 200), sf::Color(255, 255, 255, 150), i));
	}
}

void DropDownMenu::update(const sf::Vector2f& mousePos)
{
	this->activeElement->update(mousePos);

	if (this->showList)
	{
		for (auto& button : this->buttons)
		{
			button->update(mousePos);
		}
	}
}

void DropDownMenu::render()
{
	this->activeElement->render(this->window);

	if (this->showList)
	{
		for (auto& button : this->buttons)
		{
			button->render(this->window);
		}
	}
}
