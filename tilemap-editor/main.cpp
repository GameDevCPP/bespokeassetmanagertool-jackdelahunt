#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

#include "tilemap.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "nlohmann/json.hpp"
#include "level.h"

using json = nlohmann::json;

int main()
{
    std::ifstream in;
    in.open("level.json");
    json j;
    in >> j;

    level::level_data data = level::from_json(j);

    TileMap map(sf::Vector2u(data.tile_size_x, data.tile_size_y), &data.tile_ids, data.map_width, data.map_height);
    auto s = map.load("tileset.png");

    sf::RenderWindow window(sf::VideoMode(data.map_width * data.tile_size_x, data.map_height * data.tile_size_y), "Tilemap");
    ImGui::SFML::Init(window);

    int index = 0;
    int brush_size = 0;
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            auto mouse_pos = sf::Mouse::getPosition(window);
            map.update_tile(mouse_pos.x / data.tile_size_x, mouse_pos.y / data.tile_size_y, index, brush_size);
        }


        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::Begin("Pallete");
        for (int i = 0; i < s.size(); i++) {
            ImGui::Image(s.at(i)); ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::SliderInt("", &index, 0, s.size() - 1); ImGui::SameLine();
        ImGui::Image(s.at(index));
        ImGui::SliderInt("Brush Size", &brush_size, 0, 3);
        ImGui::End();

        window.clear();
        window.draw(map);
        ImGui::SFML::Render(window);
        window.display();
    }

    std::ofstream out;
    out.open("level.json");

    out << level::to_json(data);
    out.close();

    ImGui::SFML::Shutdown();
    return 0;
}