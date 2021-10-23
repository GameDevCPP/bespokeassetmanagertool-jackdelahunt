#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

    TileMap(sf::Vector2u tileSize, std::vector<int>& tiles, size_t width, size_t height) {
        m_tiles = tiles;
        m_tileSize = tileSize;
        m_width = width;
        m_height = height;
    }

    bool load(const std::string& tileset)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(m_width * m_height * 4);

        buildTexture();

        return true;
    }

    void update_tile(size_t x, size_t y, int id) {
        if (x < 0 || x > m_width) return;
        if (y < 0 || y > m_height) return;

        m_tiles.at((y * m_width) + x) = id;
        buildTexture();
    }

private:

    std::vector<int> m_tiles;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;
    size_t m_width;
    size_t m_height;

    void buildTexture() {
        // populate the vertex array, with one quad per tile
        for (unsigned int i = 0; i < m_width; ++i) {
            for (unsigned int j = 0; j < m_height; ++j)
            {
                // get the current tile number
                int tileNumber = m_tiles.at(i + j * m_width);

                // find its position in the tileset texture
                int tu = tileNumber % (m_tileset.getSize().x / m_tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / m_tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &m_vertices[(i + j * m_width) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * m_tileSize.x, j * m_tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * m_tileSize.x, j * m_tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * m_tileSize.x, (j + 1) * m_tileSize.y);
                quad[3].position = sf::Vector2f(i * m_tileSize.x, (j + 1) * m_tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * m_tileSize.x, tv * m_tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, tv * m_tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * m_tileSize.x, (tv + 1) * m_tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * m_tileSize.x, (tv + 1) * m_tileSize.y);
            }
        }
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }
};