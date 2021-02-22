#include "CellGrid.h"

// ========================== Constructors ==========================
CellGrid::CellGrid()
	: window(nullptr), position(sf::Vector2f(0, 0)), size(sf::Vector2f(0, 0)), grid(sf::Vector2f(0, 0)), startCell(nullptr), goalCell(nullptr), started(false), solve(false)
{

}

CellGrid::~CellGrid()
{
	this->stopSolve();
}


// ========================== Accessors ==========================
const unsigned short CellGrid::getStartCellIndex()
{
	if (this->startCell == nullptr)
	{
		return USHRT_MAX;
	}
	return this->startCell->getIndex();
}

const unsigned short CellGrid::getGoalCellIndex()
{
	if (this->goalCell == nullptr)
	{
		return USHRT_MAX;
	}
	return this->goalCell->getIndex();
}

const bool& CellGrid::isSolving()
{
	return this->started;
}

unsigned int CellGrid::getDistance(Cell* cell1, Cell* cell2)
{
	unsigned int x1 = cell1->getIndex() % this->grid.x;
	unsigned int y1 = cell1->getIndex() / this->grid.x;
	unsigned int x2 = cell2->getIndex() % this->grid.x;
	unsigned int y2 = cell2->getIndex() / this->grid.x;

	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

unsigned int CellGrid::getStartGoalDistance()
{
	if (!this->startCell || !this->goalCell)
	{
		std::cout << "Start or goal cell not found\n";
		return UINT_MAX;
	}
	return this->getDistance(this->startCell, this->goalCell);
}


// ========================== Functions ==========================
void CellGrid::create(sf::RenderWindow* window, sf::Vector2f pos, sf::Vector2f size, sf::Vector2i grid)
{
	this->window = window;
	this->position = pos;
	this->size = size;
	this->grid = grid;

	this->cellSize = sf::Vector2f(this->size.x / this->grid.x, this->size.y / this->grid.y);
	sf::Vector2f cellPos(0, 0);

	this->cells.resize(this->grid.x, std::vector<std::shared_ptr<Cell>>());

	for (size_t x = 0; x < this->grid.x; ++x)
	{
		this->cells[x].resize(this->grid.x, std::shared_ptr<Cell>());

		for (size_t y = 0; y < this->grid.y; ++y)
		{
			cellPos = this->position + sf::Vector2f(x * cellSize.x, y * cellSize.y);
			this->cells[x][y] = std::make_shared<Cell>(cellPos, this->cellSize, y * this->grid.x + x);
		}
	}
}

void CellGrid::updateGridSize(const unsigned short x, const unsigned short y)
{
	if (x > 0 && y > 0)
	{
		if (x != this->grid.x || y != this->grid.y)
		{
			this->startCell = nullptr;
			this->goalCell = nullptr;
			this->cells.clear();
			this->grid = sf::Vector2i(x, y);

			this->cellSize = sf::Vector2f(this->size.x / this->grid.x, this->size.y / this->grid.y);
			sf::Vector2f cellPos(0, 0);

			this->cells.resize(this->grid.x, std::vector<std::shared_ptr<Cell>>());

			for (size_t x = 0; x < this->grid.x; ++x)
			{
				this->cells[x].resize(this->grid.x, std::shared_ptr<Cell>());

				for (size_t y = 0; y < this->grid.y; ++y)
				{
					cellPos = this->position + sf::Vector2f(x * cellSize.x, y * cellSize.y);
					this->cells[x][y] = std::make_shared<Cell>(cellPos, this->cellSize, y * this->grid.x + x);
				}
			}
		}
	}
}

void CellGrid::clear()
{
	this->startCell = nullptr;
	this->goalCell = nullptr;

	for (auto& it : this->cells)
	{
		for (auto& cell : it)
		{
			cell->reset();
		}
	}
}

void CellGrid::solveAStar()
{
	this->started = true;
	bool solved = false;
	
	if (this->startCell != nullptr && this->goalCell != nullptr)
	{
		this->clearPath();
		Cell* currentCell = this->startCell;
		Cell* neighborCell = nullptr;

		sf::Vector2i direction[8] =
		{
			sf::Vector2i(1, 0),
			sf::Vector2i(1, 1),
			sf::Vector2i(0, 1),
			sf::Vector2i(-1, 1),
			sf::Vector2i(-1, 0),
			sf::Vector2i(-1, -1),
			sf::Vector2i(0, -1),
			sf::Vector2i(1, -1)
		};

		std::map<unsigned short, Cell*> cellsToCheck;
		cellsToCheck[currentCell->getIndex()] = currentCell;
		currentCell->setStartDistance(0);

		sf::Color currentColor = currentCell->getFillColor();
		
		while (cellsToCheck.size() > 0 && this->solve)
		{
			unsigned int currentStartDist = currentCell->getStartDistance();

			for (size_t i = 0; i < 8; ++i)
			{
				short x = currentCell->getIndex() % this->grid.x + direction[i].x;
				short y = currentCell->getIndex() / this->grid.x + direction[i].y;

				if (x >= 0 && x < this->grid.x && y >= 0 && y < this->grid.y)
				{
					neighborCell = this->cells[x][y].get();
					sf::Color neighborColor = neighborCell->getFillColor();

					if (neighborCell->getState() == CellState::EMPTY || neighborCell->getState() == CellState::GOAL)
					{
						unsigned int startDist = currentStartDist + this->getDistance(currentCell, neighborCell);
						unsigned int goalDist = this->getDistance(neighborCell, this->goalCell);
						if (startDist < neighborCell->getStartDistance())
						{
							neighborCell->setStartDistance(startDist);
							neighborCell->setGoalDistance(goalDist);
							neighborCell->setPrevCellIndex(currentCell->getIndex());
							cellsToCheck[neighborCell->getIndex()] = neighborCell;
						}
					}
				}
			}

			cellsToCheck.erase(currentCell->getIndex());

			if (currentCell->getState() == CellState::GOAL)
			{
				unsigned int path = 0;

				while (currentCell->getState() != CellState::START)
				{
					if (currentCell != this->goalCell)
					{
						path++;
						currentCell->setState(CellState::PATH);
						this->path.push_back(currentCell);
					}

					short x = currentCell->getPrevCellIndex() % this->grid.x;
					short y = currentCell->getPrevCellIndex() / this->grid.x;
					currentCell = this->cells[x][y].get();
				}

				this->started = false;
				return;
			}

			unsigned int shortestDist = UINT_MAX;

			for (auto& it : cellsToCheck)
			{
				if (it.second->getTotalDistance() < shortestDist)
				{
					shortestDist = it.second->getTotalDistance();
					unsigned short x = it.second->getIndex() % this->grid.x;
					unsigned short y = it.second->getIndex() / this->grid.x;
					currentCell = this->cells[x][y].get();
				}
			}
		}
	}

	this->started = false;
}

void CellGrid::clearPath()
{
	for (auto& x : this->cells)
	{
		for (auto& y : x)
		{
			y->removePath();
		}
	}

	this->path.clear();
}

void CellGrid::startAStarSolve()
{
	this->solve = true;

	if (!this->started)
	{
		this->solveThread = std::thread(&CellGrid::solveAStar, this);
		this->solveThread.detach();
	}
}

void CellGrid::stopSolve()
{
	this->solve = false;

	if (this->started)
	{
		this->solveThread.join();
	}
}

void CellGrid::update(const sf::Vector2f& mousePos, const CellState& cellState)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x >= this->position.x && mousePos.x < this->position.x + this->size.x
		&& mousePos.y >= this->position.y && mousePos.y < this->position.y + this->size.y)
	{
		
		const short x = (mousePos.x - this->position.x) / this->size.x * this->grid.x;
		const short y = (mousePos.y - this->position.y) / this->size.y * this->grid.y;

		//std::cout << "Mouse pos: " << mousePos.x << ", " << mousePos.y << std::endl;
		//std::cout << "x, y : " << x << ", " << y << std::endl;

		if (x >= 0 && x < this->grid.x && y >= 0 && y < this->grid.y)
		{
			if (this->cells[x][y]->getState() == CellState::GOAL)
			{
				this->goalCell = nullptr;
			}
			else if (this->cells[x][y]->getState() == CellState::START)
			{
				this->startCell = nullptr;
			}

			if (cellState == CellState::GOAL)
			{
				if (this->goalCell != nullptr)
				{
					this->goalCell->setState(CellState::EMPTY);
				}

				this->goalCell = this->cells[x][y].get();
			}
			else if (cellState == CellState::START)
			{
				if (this->startCell != nullptr)
				{
					this->startCell->setState(CellState::EMPTY);
				}

				this->startCell = this->cells[x][y].get();
			}

			this->cells[x][y]->setState(cellState);
		}
		
		//for (auto& x : this->cells)
		//{
		//	for (auto& y : x)
		//	{
		//		if (y.isPressed(mousePos))
		//		{
		//			if (y.getState() == CellState::GOAL)
		//			{
		//				this->goalCell = nullptr;
		//			}
		//			else if (y.getState() == CellState::START)
		//			{
		//				this->startCell = nullptr;
		//			}

		//			if (cellState == CellState::GOAL)
		//			{
		//				if (this->goalCell != nullptr)
		//				{
		//					this->goalCell->setState(CellState::EMPTY);
		//				}

		//				this->goalCell = &y;
		//			}
		//			else if (cellState == CellState::START)
		//			{
		//				if (this->startCell != nullptr)
		//				{
		//					this->startCell->setState(CellState::EMPTY);
		//				}

		//				this->startCell = &y;
		//			}

		//			y.setState(cellState);
		//			return;
		//		}
		//	}
		//}
	}
}

void CellGrid::render()
{
	for (auto& x : this->cells)
	{
		for (auto& y : x)
		{
			y->render(this->window);
		}
	}
	
}
