#pragma once

#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "CellGrid.h"
#include "DropDownMenu.h"
#include "TextField.h"
#include "StateButton.h"


class AStarPathfinding
{
private:
	// ========================== Variables ==========================
	sf::RenderWindow window;
	sf::Event sfEvent;

	std::thread updateThread;
	bool running;

	sf::RectangleShape background;
	sf::Font font;

	sf::Clock dtClock;
	float dt;

	sf::Vector2f mousePos;

	CellGrid grid;

	DropDownMenu cellTypeMenu;
	CellState currentCellState;
	std::vector<std::string> cellStateTextList;
	std::vector<CellState> cellStates;
	//std::map<std::string, CellState> cellStates;

	sf::Text startText;
	sf::Text goalText;
	sf::Text dTimeText;

	std::map<std::string, std::shared_ptr<Button>> buttons;
	std::map<std::string, std::shared_ptr<StateButton>> stateButtons;

	TextField colsInput;
	TextField rowsInput;
	TextField* activeTextField;

	// ========================== Init functions ==========================
	void initWindow();
	void initBackground();
	void initFonts();
	void initGrid();
	void initDropDownMenu();
	void initText();
	void initButtons();
	void initStateButtons();
	void initTextFields();
	void startUpdateThread();


public:
	// ========================== Constructors ==========================
	AStarPathfinding();
	virtual ~AStarPathfinding();

	// ========================== Functions ==========================
	void updateSFMLEvents();
	void updateDt();
	void updateMouse();
	void updateGrid();
	void updateDropDownMenus();
	void updateText();
	void updateButtons();
	void updateStateButtons();
	void updateTextFields();
	void update();
	void render();
	void run();
};

