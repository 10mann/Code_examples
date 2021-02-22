#include "AStarPathfinding.h"

// ========================== Init functions ==========================
void AStarPathfinding::initWindow()
{
	this->window.create(sf::VideoMode(1000, 600), "A Star Pathfinding", sf::Style::Default);
}

void AStarPathfinding::initBackground()
{
	this->background.setSize(sf::Vector2f(this->window.getSize().x, this->window.getSize().y));
	//this->background.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->background.setFillColor(sf::Color::White);
}

void AStarPathfinding::initFonts()
{
	if (!this->font.loadFromFile("Fonts/30013288172.ttf"))
	{
		throw "ERROR: AStarPathfinding: Loading font\n";
	}
}

void AStarPathfinding::initGrid()
{
	sf::Vector2f gridPos(0, 0);
	sf::Vector2f gridBoundaries(600, 600);
	sf::Vector2i gridDims(20, 20);

	this->grid.create(&this->window, gridPos, gridBoundaries, gridDims);
}

void AStarPathfinding::initDropDownMenu()
{
	this->cellStateTextList = { "Start", "Goal", "Wall", "Clear"};
	this->cellStates.clear();
	this->cellStates = { CellState::START, CellState::GOAL, CellState::WALL, CellState::EMPTY };

	sf::Vector2f cellTypeMenuSize(100, 50);
	//sf::Vector2f cellTypeMenuPos(this->window->getSize().x - cellTypeMenuSize.x, 0);
	sf::Vector2f cellTypeMenuPos(this->window.getSize().x - cellTypeMenuSize.x, 0);
	this->cellTypeMenu.create(&this->window, cellTypeMenuPos, cellTypeMenuSize, this->cellStateTextList, this->font, this->cellStateTextList.size(), this->cellStateTextList.size() - 1);
}

void AStarPathfinding::initText()
{
	this->startText.setFont(this->font);
	this->startText.setCharacterSize(22);
	this->startText.setFillColor(sf::Color::Black);
	this->startText.setPosition(600, 0);
	this->goalText.setFont(this->font);
	this->goalText.setCharacterSize(22);
	this->goalText.setFillColor(sf::Color::Black);
	this->goalText.setPosition(600, 30);

	this->dTimeText.setFont(this->font);
	this->dTimeText.setCharacterSize(22);
	this->dTimeText.setFillColor(sf::Color::Black);
	this->dTimeText.setPosition(600, 60);
}

void AStarPathfinding::initButtons()
{
	sf::Vector2f buttonSize(100, 50);
	sf::Vector2f distButtonPos(this->window.getSize().x - buttonSize.x, 320);
	sf::Vector2f solveButtonPos(distButtonPos.x, distButtonPos.y + buttonSize.y);
	sf::Vector2f clearButtonPos(distButtonPos.x, solveButtonPos.y + buttonSize.y);
	this->buttons["GET_DIST"] = std::make_shared<Button>(distButtonPos, buttonSize, "Get dist", this->font);
	this->buttons["SOLVE"] = std::make_shared<Button>(solveButtonPos, buttonSize, "Solve", this->font);
	this->buttons["CLEAR"] = std::make_shared<Button>(clearButtonPos, buttonSize, "Clear", this->font);
}

void AStarPathfinding::initStateButtons()
{
	sf::Vector2f buttonSize(100, 50);
	sf::Vector2f solveButtonPos(this->window.getSize().x - buttonSize.x, 370);

	//this->stateButtons["SOLVE"] = std::make_shared<StateButton>(solveButtonPos, buttonSize, "Solve", this->font);
}

void AStarPathfinding::initTextFields()
{
	sf::Vector2f textFieldSize(60, 30);
	sf::Vector2f inputColsPos(this->window.getSize().x -  2 * textFieldSize.x, 500);
	sf::Vector2f inputRowsPos(inputColsPos.x + textFieldSize.x, inputColsPos.y);

	this->colsInput.create(inputColsPos, textFieldSize, this->font);
	this->rowsInput.create(inputRowsPos, textFieldSize, this->font);

	sf::Vector2f buttonSize(2 * textFieldSize.x, 40);
	sf::Vector2f buttonPos(inputColsPos.x, inputColsPos.y + textFieldSize.y);
	this->buttons["APPLY"] = std::make_shared<Button>(buttonPos, buttonSize, "Apply", this->font);
}

void AStarPathfinding::startUpdateThread()
{
	this->running = true;
	this->updateThread = std::thread(&AStarPathfinding::update, this);
}


// ========================== Constructors ==========================
AStarPathfinding::AStarPathfinding()
	: currentCellState(CellState::EMPTY), running(false)
{
	this->initWindow();
	this->initBackground();
	this->initFonts();
	this->initGrid();
	this->initDropDownMenu();
	this->initText();
	this->initButtons();
	this->initStateButtons();
	this->initTextFields();
}

AStarPathfinding::~AStarPathfinding()
{
	this->running = false;
	this->updateThread.join();
}


// ========================== Functions ==========================
void AStarPathfinding::updateSFMLEvents()
{
	while (this->window.pollEvent(this->sfEvent))
	{
		switch (this->sfEvent.type)
		{
		case sf::Event::Closed:
			this->grid.stopSolve();
			this->running = false;
			this->window.close();
			break;

		case sf::Event::KeyPressed:

			break;

		case sf::Event::TextEntered:
			if (this->activeTextField != nullptr)
			{
				this->activeTextField->updateText(sfEvent.text.unicode);
			}
			break;

		case sf::Event::MouseButtonPressed:
			std::cout << "Mouse pressed: (" << this->mousePos.x << ", " << this->mousePos.y << ")\n";
			this->activeTextField = nullptr;

			if (this->buttons["GET_DIST"]->isPressed(this->mousePos))
			{
				std::cout << "Start - goal dist: " << this->grid.getStartGoalDistance() << std::endl;
			}
			else if (this->buttons["SOLVE"]->isPressed(this->mousePos))
			{
				std::cout << "Solve\n";
				this->grid.startAStarSolve();
			}
			else if (this->buttons["CLEAR"]->isPressed(this->mousePos))
			{
				std::cout << "Clear\n";
				this->grid.clear();
			}
			else if (this->buttons["APPLY"]->isPressed(this->mousePos))
			{
				std::cout << "Apply\n";

				this->grid.updateGridSize(this->colsInput.getInputValue(), this->rowsInput.getInputValue());
			}
			if (this->cellTypeMenu.isPressed(this->mousePos))
			{
				this->currentCellState = this->cellStates[this->cellTypeMenu.getActiveElementIndex()];
			}
			if (this->colsInput.isPressed(this->mousePos))
			{
				this->activeTextField = &this->colsInput;
			}
			if (this->rowsInput.isPressed(this->mousePos))
			{
				this->activeTextField = &this->rowsInput;
			}
			break;
		}
	}
}

// Update time between frames
void AStarPathfinding::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void AStarPathfinding::updateMouse()
{
	this->mousePos = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

void AStarPathfinding::updateGrid()
{
	this->grid.update(this->mousePos, this->currentCellState);
}

void AStarPathfinding::updateDropDownMenus()
{
	this->cellTypeMenu.update(this->mousePos);

}

void AStarPathfinding::updateText()
{

	this->startText.setString("Start: " + std::to_string(this->grid.getStartCellIndex()));
	this->goalText.setString("Goal: " + std::to_string(this->grid.getGoalCellIndex()));

	this->dTimeText.setString("dt: " + std::to_string(this->dt));
}

void AStarPathfinding::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePos);
	}
}

void AStarPathfinding::updateStateButtons()
{

}

void AStarPathfinding::updateTextFields()
{
	this->colsInput.update(this->mousePos);

	this->rowsInput.update(this->mousePos);
}

// Updating state and checking for new input
void AStarPathfinding::update()
{
	while (this->running)
	{
		this->updateDt();
		this->updateMouse();
		//this->updateSFMLEvents();
		this->updateText();
		this->updateButtons();
		this->updateStateButtons();
		this->updateDropDownMenus();
		this->updateGrid();
		//this->updateText();
		this->updateTextFields();
	}
}

// Rendering state to the screen
void AStarPathfinding::render()
{

	this->updateSFMLEvents();
	//std::cout << "Running\n";
	
	this->window.clear();
		
	this->window.draw(background);
	this->grid.render();
	this->cellTypeMenu.render();
	this->window.draw(this->startText);
	this->window.draw(this->goalText);
	this->colsInput.render(&this->window);
	this->rowsInput.render(&this->window);
	this->window.draw(this->dTimeText);

	for (auto& it : this->buttons)
	{
		it.second->render(&this->window);
	}

	for (auto& it : this->stateButtons)
	{
		it.second->render(&this->window);
	}

	this->window.display();

}

// Looping while the window is open
void AStarPathfinding::run()
{
	//this->running = true;
	this->startUpdateThread();

	while (this->running/*this->window.isOpen()*/)
	{		
		//this->update();

		this->render();
	}
}
