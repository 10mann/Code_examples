#pragma once

#include <vector>
#include <thread>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "sequence_box.h"


class SequenceGrid
{
private:
	sf::RenderWindow* window;
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Vector2f grid;
	sf::Vector2f boxSpace;
	sf::RectangleShape boundaries;
	sf::Vector2f boxSize;
	std::vector<Box> boxes;
	std::vector<sf::SoundBuffer> sounds;

	int activeBoxes;

public:
	// ================ Constructors ================
	SequenceGrid(sf::RenderWindow* window);

	// ================ Functions ================
	void create(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f grid);
	bool setSounds(std::vector<sf::SoundBuffer>& sounds);

	void setBoxState(int boxIndex, bool state);
	void reset();

	void draw();
};