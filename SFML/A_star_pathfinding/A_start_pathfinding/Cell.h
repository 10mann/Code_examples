#pragma once

#include "SFML/Graphics.hpp"

enum class CellState 
{
	EMPTY,
	WALL,
	START,
	GOAL,
	PATH
};


class Cell : public sf::RectangleShape
{
private:
	// Variables
	unsigned short index;
	unsigned short prevCellIndex;
	unsigned int startDistance;
	unsigned int goalDistance;
	CellState state;
	sf::Color defaultColor;
	sf::Color wallColor;
	sf::Color startColor;
	sf::Color goalColor;
	sf::Color pathColor;

	bool checked;

public:
	//  ========================== Constructors ==========================
	Cell();
	Cell(sf::Vector2f pos, sf::Vector2f size, unsigned short index);
	virtual ~Cell();

	// ========================== Accessors ==========================
	bool isPressed(sf::Vector2f mousePos);
	void setState(CellState state);
	const CellState& getState();
	const unsigned short getIndex();
	void setPrevCellIndex(const unsigned short index);
	const unsigned short getPrevCellIndex();
	void setStartDistance(const unsigned int startDistance);
	const unsigned int getStartDistance();
	void setGoalDistance(const unsigned int goalDistance);
	const unsigned int getGoalDistance();
	const unsigned int getTotalDistance();
	const bool& isChecked();
	void setChecked(bool checked);

	// ========================== Functions ==========================
	void reset();
	void removePath();
	void render(sf::RenderWindow* window);
};