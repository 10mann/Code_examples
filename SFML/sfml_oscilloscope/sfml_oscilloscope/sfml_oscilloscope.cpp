#include <iostream>
#include <SFML\Graphics.hpp>
#include "serial_port.h"
#include "serial_port_poll.h"
#include <thread>


int sample_frequency;

int main()
{
    // Window
    int window_width = 800;
    int window_height = 600;
    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML Oscilloscope", sf::Style::Close | sf::Style::Titlebar);
    sf::Event evnt;

    std::chrono::steady_clock::time_point last_time = std::chrono::steady_clock::now();
    int fps = 0;
    // Serial buffer
    const int serial_data_max_value = 1024;
    const int serial_buffer_size = 1024;
    int serial_buffer[serial_buffer_size] = { 0 };

    // Starting serial polling
    std::thread serial_poll_thread(poll_serial_data, serial_buffer, serial_buffer_size);

    // Fonts
    sf::Font font;
    if (!font.loadFromFile("Fonts/Roboto-Thin.ttf"))
        std::cout << "Unable to load font";

    // Text
    sf::Text sample_freq_text;
    sample_freq_text.setFont(font);
    sample_freq_text.setFillColor(sf::Color::Black);

    sf::Text fps_text;
    fps_text.setFont(font);
    fps_text.setFillColor(sf::Color::Black);
    fps_text.setPosition(sf::Vector2f(window_width - 150, 5));



    sf::Vertex line[2];
    line[0].color = sf::Color::Blue;
    line[1].color = sf::Color::Blue;

    // Window loop
    while (window.isOpen())
    {
        
        // Event loop
        while (window.pollEvent(evnt))
        {
            
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        // Calculating fps
        std::chrono::duration<double> time_diff = (std::chrono::steady_clock::now() - last_time);
        fps = std::chrono::seconds(1) / time_diff;
        last_time = std::chrono::steady_clock::now();

        // Displaying text
        sample_freq_text.setString("Sample frequency: " + std::to_string(sample_frequency));
        fps_text.setString("FPS: " + std::to_string(fps));
        // Updating display
        window.clear(sf::Color::White);

        // Drawing graph from serial data
        for (int i = 1; i < serial_buffer_size; i++)
        {
            line[0].position = sf::Vector2f(((float)i / (float)serial_buffer_size) * window_width, window_height - ((float)serial_buffer[i] / (float)serial_data_max_value) * window_height);
            line[1].position = sf::Vector2f(((float)(i - 1) / (float)serial_buffer_size) * window_width, window_height - ((float)serial_buffer[i - 1] / (float)serial_data_max_value) * window_height);

            window.draw(line, 2, sf::Lines);
        }


        window.draw(sample_freq_text);
        window.draw(fps_text);
        window.display();

    }

    serial_poll_thread.detach();

    return 0;
}
