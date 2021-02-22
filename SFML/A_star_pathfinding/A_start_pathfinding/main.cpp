#include <iostream>
#include <string>

#include "SFML/Graphics.hpp"
#include "CellGrid.h"
#include "TextField.h"
#include "DropDownMenu.h"
#include "AStarPathfinding.h"


int main()
{
    AStarPathfinding aStar;

    aStar.run();

    return 0;
}