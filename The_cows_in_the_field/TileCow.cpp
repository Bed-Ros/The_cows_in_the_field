#include <SFML/Graphics.hpp>

class TileCow : public sf::Drawable, public sf::Transformable
{
public:

	bool load(const std::string& tileset, sf::Vector2u textureSize, sf::Vector2u tileSize, sf::Vector2u location = sf::Vector2u(0, 0), std::string direction = "left")
	{
		// загрузка файла текстур
		if (!c_tileset.loadFromFile(tileset))
			return false;

		c_vertices.setPrimitiveType(sf::Quads);
		c_vertices.resize(4);
		//
		c_location = location;
		c_tile_size = tileSize;
		c_texture_size = textureSize;
		//назначение первоначальной позиции
		update_location();
		//назначение первоначальной текстуры
		update_texture(direction);

		return true;
	}

	void go_up() {
		c_location -= sf::Vector2u(0, 1);
		update_location();
	}

	void go_down() {
		c_location += sf::Vector2u(0, 1);
		update_location();
	}

	void go_left() {
		c_location -= sf::Vector2u(1, 0);
		update_location();
		update_texture("left");
	}

	void go_right() {
		c_location += sf::Vector2u(1, 0);
		update_location();
		update_texture("right");
	}

private:

	void update_location() {
		c_vertices[0].position = sf::Vector2f(c_location.x * c_tile_size.x, c_location.y * c_tile_size.y);
		c_vertices[1].position = sf::Vector2f((c_location.x + 1) * c_tile_size.x, c_location.y * c_tile_size.y);
		c_vertices[2].position = sf::Vector2f((c_location.x + 1) * c_tile_size.x, (c_location.y + 1) * c_tile_size.y);
		c_vertices[3].position = sf::Vector2f(c_location.x * c_tile_size.x, (c_location.y + 1) * c_tile_size.y);
	}

	void update_texture(std::string direction) {

		if (direction == "right") {
			c_vertices[0].texCoords = sf::Vector2f(c_texture_size.x, 0);
			c_vertices[1].texCoords = sf::Vector2f(0, 0);
			c_vertices[2].texCoords = sf::Vector2f(0, c_texture_size.y);
			c_vertices[3].texCoords = sf::Vector2f(c_texture_size.x, c_texture_size.y);
		}
		else {// по умолчанию влево
			c_vertices[0].texCoords = sf::Vector2f(0, 0);
			c_vertices[1].texCoords = sf::Vector2f(c_texture_size.x, 0);
			c_vertices[2].texCoords = sf::Vector2f(c_texture_size.x, c_texture_size.y);
			c_vertices[3].texCoords = sf::Vector2f(0, c_texture_size.y);
		}
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &c_tileset;

		// draw the vertex array
		target.draw(c_vertices, states);
	}

	sf::VertexArray c_vertices;
	sf::Texture c_tileset;
	sf::Vector2u c_location;
	sf::Vector2u c_texture_size;
	sf::Vector2u c_tile_size;

};