#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(240 * 4, 160 * 4), "SFML works!");
	window.setFramerateLimit(60);

	sf::Texture overworldTex;
	overworldTex.loadFromFile("Media/Coneha.png");

	sf::Sprite overworld(overworldTex);
	overworld.scale(sf::Vector2f(4.f, 4.f));

	sf::Vector2f mapSpeed(0.f, 0.f);
	int fast = 3;

	// Main loop
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();
		// Process Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			mapSpeed.y = 200.f * 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			mapSpeed.x = 200.f * 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			mapSpeed.y = -200.f * 4;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			mapSpeed.x = -200.f * 4;

		mapSpeed *= deltaTime.asSeconds();

		// Update
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
			overworld.move(mapSpeed.x* fast, mapSpeed.y * fast);
		else
			overworld.move(mapSpeed.x, mapSpeed.y);

		// Render
		window.clear();

		window.draw(overworld);
		//window.draw(character);

		window.display();
	}

	return 0;
}