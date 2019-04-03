#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u textureSize, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
	{
		// загрузка файла текстур
		if (!m_tileset.loadFromFile(tileset))
			return false;

		// изменение размера массива вершин в соответствии с размером уровня
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		// заполнение массива вершин одним квадратом на плитку
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// получить текущий номер плитки
				int tileNumber = tiles[i + j * width];

				// найти его положение в общей текстуре
				int tu = tileNumber % (m_tileset.getSize().x / textureSize.x);
				int tv = tileNumber / (m_tileset.getSize().x / textureSize.x);

				// получить указатель на квадрат текущей плитки
				sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

				// определить его 4 угла
				quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
				quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
				quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

				// определите 4 координаты текстуры
				quad[0].texCoords = sf::Vector2f(tu * textureSize.x, tv * textureSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * textureSize.x, tv * textureSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * textureSize.x, (tv + 1) * textureSize.y);
				quad[3].texCoords = sf::Vector2f(tu * textureSize.x, (tv + 1) * textureSize.y);
			}

		return true;
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &m_tileset;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;
};