#include <SFML/Graphics.hpp>
#include "tilemap.h"
#include <iostream>

const size_t t_width = 16;
const size_t t_height = 8;
const size_t t_size = 32;

int main()
{
    auto level = std::vector<int> {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    TileMap map(sf::Vector2u(t_size, t_size), level, t_width, t_height);
    if (!map.load("tileset.png"))
        return -1;

    sf::RenderWindow window(sf::VideoMode(t_width * t_size, t_height * t_size), "Tilemap");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto mouse_pos = sf::Mouse::getPosition(window);
            map.update_tile(mouse_pos.x / t_size, mouse_pos.y / t_size, 0);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            auto mouse_pos = sf::Mouse::getPosition(window);
            map.update_tile(mouse_pos.x / t_size, mouse_pos.y / t_size, 1);
        }

        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}