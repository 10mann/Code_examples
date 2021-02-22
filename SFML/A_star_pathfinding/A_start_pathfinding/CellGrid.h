#pragma once

#include <iostream>
#include <vector>
#include <thread>

#include "Cell.h"


class CellGrid
{
private:
	// ========================== Variables ==========================
	sf::RenderWindow* window;
	sf::Vector2f position;
	sf::Vector2i grid;
	sf::Vector2f size;
	sf::Vector2f cellSize;

	//std::vector<std::vector<Cell>> cells;
	std::vector<std::vector<std::shared_ptr<Cell>>> cells;

	Cell* startCell;
	Cell* goalCell;

	bool started;
	std::vector<Cell*> path;

	bool solve;
	std::thread solveThread;

	// ========================== Functions ==========================
	void solveAStar();
	void clearPath();

public:
	// ========================== Constructors ==========================
	CellGrid();
	virtual ~CellGrid();

	// ========================== Accessors ==========================
	const unsigned short getStartCellIndex();
	const unsigned short getGoalCellIndex();
	const bool& isSolving();

	// ========================== Functions ==========================
	unsigned int getDistance(Cell* cell1, Cell* cell2);
	unsigned int getStartGoalDistance();
	void create(sf::RenderWindow* window, sf::Vector2f pos, sf::Vector2f size, sf::Vector2i grid);
	void updateGridSize(const unsigned short x, const unsigned short y);
	void clear();
	void startAStarSolve();
	void stopSolve();
	void update(const sf::Vector2f& mousePos, const CellState& cellState);
	void render();
};