#include <iostream>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <vector>

std::pair<int, int> addPair(std::pair<int, int> a, std::pair<int, int> b)
{
	return { a.first + b.first, a.second + b.second };
}

void printPair(std::pair<int, int> pair)
{
	std::cout << "{" << pair.first << ", " << pair.second << "}\n";
}


class Maze : public olc::PixelGameEngine
{
public:
	int rows, cols;
	int screen_width, screen_height;
	int cell_size, wall_width;
	int visited_cells;
	std::pair<int, int> next_dir[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
	std::pair<int, int> next_cell;
	std::pair<int, int> current_cell = { 0, 0 };
	std::vector<std::pair<int, int>> cell_path;
	olc::Pixel background = olc::WHITE;

	bool* cell;

	Maze(int rows, int cols, int cell_size, int wall_width)
	{

		sAppName = "Maze_algorithm";
		this->rows = rows;
		this->cols = cols;
		this->wall_width = wall_width;
		this->cell_size = cell_size;
		this->screen_width = this->rows * this->cell_size + (this->rows + 1) * this->wall_width;
		this->screen_height = this->cols * this->cell_size + (this->cols + 1) * this->wall_width;

		this->cell = new bool[this->rows * this->cols];

		memset(this->cell, true, this->rows * this->cols);

		this->visited_cells = 0;
	}

	~Maze()
	{
		delete[] cell;
	}

	bool OnUserCreate()
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				drawRect(i, j, this->background);
				//drawCellNumber(i, j);
			}
		}

		this->cell[0] = false;
		this->visited_cells = 1;
		this->cell_path.push_back(this->current_cell);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		if (this->visited_cells < this->rows * this->cols)
		{
			this->next_cell = addPair(this->current_cell, this->next_dir[std::rand() % 4]);

			if (cellLinkIsValid(this->next_cell))
			{
				removeWall(this->current_cell, this->next_cell);
				this->current_cell = this->next_cell;
				unvalidateCell(this->current_cell);
				this->visited_cells++;
				this->cell_path.push_back(this->current_cell);
			}


			if (!validNeighboor(this->current_cell))
			{
				std::cout << this->cell_path.size() << std::endl;
				this->cell_path.pop_back();
				this->current_cell = *(this->cell_path.end() - 1);
			}

			if (this->visited_cells == this->rows * this->cols)
			{
				drawCell(this->current_cell, this->background);
				drawCell({ 0, 0 }, olc::GREY);
				drawCell({std::rand() % this->rows, std::rand() % this->cols}, olc::GREY);
				std::cout << "Done\n";
				std::cout << "Goal: ";
				printPair(this->current_cell);

				for (auto& it : this->cell_path)
					printPair(it);
			}
		}

		return true;
	}

	bool cellIsValid(std::pair<int, int> cell)
	{
		if (cell.first < 0 || cell.first > this->rows - 1 || cell.second < 0 || cell.second > this->cols - 1)
			return false;

		return this->cell[cell.second * this->rows + cell.first];
	}

	void unvalidateCell(std::pair<int, int> cell)
	{
		this->cell[cell.second * this->rows + cell.first] = false;
	}

	bool validNeighboor(std::pair<int, int> cell)
	{
		for (int i = 0; i < sizeof(this->next_dir) / sizeof(this->next_dir[0]); i++)
		{
			if (cellIsValid(addPair(cell, this->next_dir[i])))
			{
				return true;
			}
		}

		return false;
	}

	std::pair<int, int> getCellCoordinates(std::pair<int, int> cell)
	{
		return { cell.first * this->cell_size + (cell.first + 1) * this->wall_width, cell.second * this->cell_size + (cell.second + 1) * this->wall_width };
	}

	void drawCell(std::pair<int, int> cell, olc::Pixel color)
	{
		drawRect(cell.first, cell.second, color);
	}

	void drawCellNumber(int i, int j)
	{
		DrawString({ i * this->cell_size + (i + 1) * this->wall_width, j * this->cell_size + (j + 1) * this->wall_width }, std::to_string(j * this->rows + i), olc::BLACK, 1);
	}

	void drawRect(int x, int y, olc::Pixel color)
	{
		FillRect({ x * this->cell_size + (x + 1) * this->wall_width, y * this->cell_size + (y + 1) * this->wall_width }, { this->cell_size, this->cell_size }, color);
	}

	void drawRectByIndex(int index, olc::Pixel color)
	{
		drawRect(index % this->rows, index / this->cols, color);
	}

	void removeWall(std::pair<int, int> current_cell, std::pair<int, int> next_cell)
	{
		int x = current_cell.first * this->cell_size + (current_cell.first + 1) * this->wall_width;
		int y = current_cell.second * this->cell_size + (current_cell.second + 1) * this->wall_width;

		if (current_cell.first < next_cell.first)
			x += this->wall_width;
		else if (current_cell.first > next_cell.first)
			x -= this->wall_width;

		if (current_cell.second < next_cell.second)
			y += this->wall_width;
		else if (current_cell.second > next_cell.second)
			y -= this->wall_width;

		FillRect({ x , y }, { this->cell_size, this->cell_size }, this->background);
	}

	bool cellLinkIsValid(std::pair<int, int> next_cell)
	{
		if (next_cell.first > -1 && next_cell.first < this->rows && next_cell.second > -1 && next_cell.second < this->cols && cellIsValid(next_cell))
			return true;

		return false;
	}
};


int main()
{
	Maze maze(72, 38, 10, 2);

	std::cout << "Rows: " << maze.rows << " , Cols: " << maze.cols << " , Width: " << maze.screen_width << " , Height: " << maze.screen_height << std::endl;

	if (maze.Construct(maze.screen_width, maze.screen_height, 2, 2))
		maze.Start();

	return 0;
}

