#include "sequence_grid.h"

// ================ Constructors ================
SequenceGrid::SequenceGrid(sf::RenderWindow* window)
{
	this->window = window;
	this->activeBoxes = 0;
}

// ================ Functions ================

// Used to create a grid at the desired position with a given size
void SequenceGrid::create(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f grid)
{
	this->pos = pos;
	this->size = size;
	this->grid = grid;
	
	this->boundaries = sf::RectangleShape(this->size);
	this->boundaries.setPosition(this->pos);
	this->boundaries.setFillColor(sf::Color(0, 0, 0));

	float spaceFactor = 20.0;

	this->boxSpace = sf::Vector2f(this->size. x / spaceFactor, this->size.y / spaceFactor);

	this->boxSize = sf::Vector2f((this->size.x - this->boxSpace.x * (this->grid.x + 1)) / this->grid.x, (this->size.y - this->boxSpace.y * (this->grid.y + 1)) / this->grid.y);

	for (int i = 0; i < this->grid.y; i++)
	{
		for (int j = 0; j < this->grid.x; j++)
		{
			Box box = Box(this->boxSize);
			box.setPosition(this->pos + sf::Vector2f(j * (this->boxSize.x + this->boxSpace.x) + this->boxSpace.x, i * (this->boxSize.y + this->boxSpace.y) + this->boxSpace.y));
			box.setFillColor(sf::Color(0, 255, 255));
			this->boxes.push_back(box);
		}
	}
}

// Sets the sounds that should be played when a cell is activated
bool SequenceGrid::setSounds(std::vector<sf::SoundBuffer>& sounds)
{
	this->sounds = sounds;

	if (this->sounds.size() != this->boxes.size())
	{
		return false;
	}

	for (int i = 0; i < this->boxes.size(); i++)
	{
		this->boxes[i].setSound(this->sounds[i]);
	}
}

// Sets a cell to a given state
void SequenceGrid::setBoxState(int boxIndex, bool state)
{
	if(boxIndex >= 0 && boxIndex < this->boxes.size())
		this->boxes[boxIndex].setState(state);
}

// Resets all cells
void SequenceGrid::reset()
{
	for (auto& box : this->boxes)
	{
		box.setState(false);
	}
}

// Used to draw the grid to the screen
void SequenceGrid::draw()
{
	this->window->draw(this->boundaries);

	for (auto& box : this->boxes)
	{
		if (box.isActive())
			this->window->draw(box);
	}
}