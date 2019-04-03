#include <SFML/Window.hpp>

#include "TileMap.cpp"
#include "TileCow.cpp"

int main()
{
	const static int w_matrix_size = 20;
	const static int h_matrix_size = 10;

	// уровень с массивом индексов плиток
	const int level[w_matrix_size*h_matrix_size] =
	{
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
	};

	static int texture_size = 32;
	static int tile_size = 64;

	static int window_width = tile_size * w_matrix_size;
	static int window_height = tile_size * h_matrix_size;

	int cow_x = w_matrix_size / 2;
	int cow_y = h_matrix_size / 2;

	std::string tileset = "tile_textures.png";

	// создание окна
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tilemap");

	// Создать карту из массива уровня
	TileMap map;
	if (!map.load(tileset, sf::Vector2u(texture_size, texture_size), sf::Vector2u(tile_size, tile_size), level, w_matrix_size, h_matrix_size))
		return -1;
	//Создать корову
	TileCow cow;
	if (!cow.load(tileset, sf::Vector2u(texture_size, texture_size), sf::Vector2u(tile_size, tile_size), sf::Vector2u(cow_x, cow_y)))
		return -1;

	// главный цикл
	while (window.isOpen())
	{
		// обработка событий
		sf::Event event;
		while (window.pollEvent(event))
		{
			// закрытие
			if (event.type == sf::Event::Closed)
				window.close();
			//Управление коровой
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W)
					cow.go_up();
				if (event.key.code == sf::Keyboard::S)
					cow.go_down();
				if (event.key.code == sf::Keyboard::A)
					cow.go_left();
				if (event.key.code == sf::Keyboard::D)
					cow.go_right();
			}

		}

		// рисовка карты
		window.clear();
		window.draw(map);
		window.draw(cow);
		window.display();
	}

	return 0;
}