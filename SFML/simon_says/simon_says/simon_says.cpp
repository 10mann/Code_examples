#include <iostream>
#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "button_panel.h"
#include "light_cluster.h"
#include "sequence_FSM.h"
#include "sequence_grid.h"
#include "button_sounds.h"


int main()
{
    // Creating game window with set size
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Simon Says", sf::Style::Titlebar | sf::Style::Close);
    sf::Event windowEvent;


    /*  Buttons */
    ButtonPanel inputButtonGrid(&window);
    std::vector<sf::SoundBuffer> inputButtonSounds;
    if (!initInputButtonSounds(inputButtonSounds))
        printf("Error initing button sounds\n");

    if (!inputButtonGrid.createButtonGrid(sf::Vector2f(560, 200), sf::Vector2f(300, 300), sf::Vector2f(3, 3)))
        printf("Error creating button panel\n");

    inputButtonGrid.setButtonSounds(inputButtonSounds);

    /*  Lights */
    sf::Texture lightOnTexture;
    sf::Texture lightOffTexture;
    int numberOfLights = 5;
    int numberOfLitLights = 0;
    LightCluster score(&window);
    if (!score.createDefaultCluster(sf::Vector2f(560, 100), 300, numberOfLights))
    {
        printf("Error creating light cluster\n");
    }

    /*  Game grid   */
    SequenceGrid sequenceGrid(&window);
    sequenceGrid.create(sf::Vector2f(60, 200), sf::Vector2f(300, 300), sf::Vector2f(3, 3));
    sequenceGrid.setSounds(inputButtonSounds);

    /*  Game FSM    */
    SequenceFSM fsm(5);
    fsm.setGrid(&sequenceGrid);
    fsm.setInputPanel(&inputButtonGrid);
    fsm.setLightCluster(&score);
    fsm.start();
    int activeBoxes = 0;


    sf::Vertex midLine[] =
    {
        sf::Vertex(sf::Vector2f(window.getSize().x / 2.0f, 0)),
        sf::Vertex(sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y))
    };

    while (window.isOpen())
    {
        // Polling events to check for user input
        while (window.pollEvent(windowEvent))
        {
            if (windowEvent.type == sf::Event::Closed)
            {
                fsm.stop();
                window.close();
            }

            else if (windowEvent.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0.0f, 0.0f, windowEvent.size.width, windowEvent.size.height);
                window.setView(sf::View(visibleArea));
            }

            else if (windowEvent.mouseButton.button == sf::Mouse::Left)
            {
                if (windowEvent.type == sf::Event::MouseButtonPressed)
                {
                    //printf("Button %i pressed\n", inputButtonGrid.getButtonPressedIndex(sf::Mouse::getPosition(window)));
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);

                    int pressedButton = 0;
                    if (inputButtonGrid.pressed(mouse))
                    {
                        //pressedButton = inputButtonGrid.getButtonPressedIndex();
                        //printf("Button %i pressed\n", pressedButton);
                    }
                }

                else if (windowEvent.type == sf::Event::MouseButtonReleased)
                {
                    inputButtonGrid.resetButton();
                }
            }
        }

        
        window.clear(sf::Color(150, 150, 150));

        window.draw(midLine, 2, sf::Lines);

        sequenceGrid.draw();
        inputButtonGrid.draw();
        score.draw();

        window.display();
    }
    
}
