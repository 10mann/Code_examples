#include "Cell.h"


// ========================== Constructors ==========================
Cell::Cell()
	: index(0), state(CellState::EMPTY), defaultColor(sf::Color::White), wallColor(sf::Color::Black), startColor(sf::Color::Blue), goalColor(sf::Color::Blue), pathColor(sf::Color::Cyan),
	prevCellIndex(0), goalDistance(UINT_MAX), startDistance(UINT_MAX), checked(false)
{
}

Cell::Cell(sf::Vector2f pos, sf::Vector2f size, unsigned short index)
	: index(index), state(CellState::EMPTY), defaultColor(sf::Color::White), wallColor(sf::Color::Black), startColor(sf::Color::Blue), goalColor(sf::Color::Blue), pathColor(sf::Color::Cyan),
	prevCellIndex(0), goalDistance(UINT_MAX), startDistance(UINT_MAX), checked(false)
{
	this->setPosition(pos);
	this->setSize(size);

	this->setFillColor(this->defaultColor);
	this->setOutlineThickness(1.0f);
	this->setOutlineColor(sf::Color::Black);
}

Cell::~Cell()
{

}


// ========================== Accessors ==========================
bool Cell::isPressed(sf::Vector2f mousePos)
{
	return this->getGlobalBounds().contains(mousePos);
}

void Cell::setState(CellState state)
{
	this->state = state;

	switch (this->state)
	{
	case CellState::EMPTY:
		this->setFillColor(this->defaultColor);
		break;

	case CellState::WALL:
		this->setFillColor(this->wallColor);
		break;

	case CellState::START:
		this->setFillColor(this->startColor);
		break;

	case CellState::GOAL:
		this->setFillColor(this->goalColor);
		break;

	case CellState::PATH:
		this->setFillColor(this->pathColor);
		break;
	}
}

const CellState& Cell::getState()
{
	return this->state;
}

const unsigned short Cell::getIndex()
{
	return this->index;
}

void Cell::setPrevCellIndex(const unsigned short index)
{
	this->prevCellIndex = index;
}

const unsigned short Cell::getPrevCellIndex()
{
	return this->prevCellIndex;
}

void Cell::setStartDistance(const unsigned int startDistance)
{
	this->startDistance = startDistance;
}

const unsigned int Cell::getStartDistance()
{
	return this->startDistance;
}

void Cell::setGoalDistance(const unsigned int goalDistance)
{
	this->goalDistance = goalDistance;
}

const unsigned int Cell::getGoalDistance()
{
	return this->goalDistance;
}

const unsigned int Cell::getTotalDistance()
{
	return this->startDistance + this->goalDistance;
}

const bool& Cell::isChecked()
{
	return this->checked;
}

void Cell::setChecked(bool checked)
{
	this->checked = checked;
}


void Cell::reset()
{
	this->setState(CellState::EMPTY);
	this->goalDistance = UINT_MAX;
	this->startDistance = UINT_MAX;
	this->prevCellIndex = 0;
	this->checked = false;
}

void Cell::removePath()
{
	if (this->state == CellState::PATH)
	{
		this->setState(CellState::EMPTY);
	}
	this->goalDistance = UINT_MAX;
	this->startDistance = UINT_MAX;
	this->prevCellIndex = 0;
	this->checked = false;
}

// ========================== Functions ==========================
void Cell::render(sf::RenderWindow* window)
{ 
	if (this)
	{
		window->draw(*this);
	}
}
