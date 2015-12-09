#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 480

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Mode 7 Test");
	window.setFramerateLimit(60);

	auto offset = sf::Vector2f(-0.5f, 0.5f);
	float scaling = 0.1f;
	float fov = 0.5f;
	float angle = 0.0f;

	sf::Texture texture;
	texture.loadFromFile("Media/mapborder.png");
	//texture.setRepeated(true);

	sf::RectangleShape map;
	map.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	sf::Shader mode7;
	mode7.loadFromFile("Media/mode7.frag", sf::Shader::Fragment);
	mode7.setParameter("resolution", sf::Vector2f(window.getSize()));
	mode7.setParameter("texture", texture);
	mode7.setParameter("offset", offset.x, offset.y);
	mode7.setParameter("fov", fov);
	mode7.setParameter("scaling", scaling);
	mode7.setParameter("angle", angle);

	while (window.isOpen())
	{
		// Process Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			offset.y += 0.01f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			offset.x += 0.01f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			offset.y -= 0.01f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			offset.x -= 0.01f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
			scaling += 0.01f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
			scaling -= 0.01f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			angle += 0.1f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			angle -= 0.1f;

		// Update
		mode7.setParameter("offset", offset);
		mode7.setParameter("scaling", scaling);
		mode7.setParameter("angle", angle);

		// Render
		window.clear();
		window.draw(map, &mode7);
		window.display();
	}

	return 0;
}
