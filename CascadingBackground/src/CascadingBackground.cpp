#include <SFML/Graphics.hpp>

const int window_width = 240;
const int window_height = 160;
const float speed = 15.f;
const int scale = 2;

int main()
{
	sf::RenderWindow window(sf::VideoMode(window_width * scale,
										  window_height * scale),
							"Yay GBA!");
	window.setFramerateLimit(60);

	sf::Texture backgroundTex;
	backgroundTex.loadFromFile("Media/Machinesbgpink.png");
	backgroundTex.setRepeated(true);

	sf::Texture foregroundTex;
	foregroundTex.loadFromFile("Media/Machinesfgpink.png");
	foregroundTex.setRepeated(true);

	sf::Texture dialogueTex;
	dialogueTex.loadFromFile("Media/DialogueBox.png");

	sf::Sprite background(backgroundTex);
	//background.setColor(COLOR_VARIABLE); can't figure out the color modulation!!
	background.setTextureRect(sf::IntRect(0, 0, 368, 288)); // Get (64+240+64)x(64+160+64) of texture
	background.setOrigin(64, 64);
	background.scale(sf::Vector2f(scale, scale));
	//background.setPosition(0, 0); //implied

	sf::Sprite foreground(foregroundTex);
	//foreground.setColor(COLOR_VARIABLE);
	foreground.setTextureRect(sf::IntRect(0, 0, 368, 288));
	foreground.setOrigin(64, 64);
	foreground.scale(sf::Vector2f(scale, scale));
	//foreground.setPosition(0, 0); //implied

	sf::Sprite dialogue;
	dialogue.setTexture(dialogueTex);
	dialogue.setPosition(32 * scale, 70 * scale);
	dialogue.scale(sf::Vector2f(scale, scale));

	float x_direction = 1;
	float y_direction = -1;

	// Main loop
	sf::Clock clock;
	while (window.isOpen())
	{
		// Get deltaTime
		sf::Time deltaTime = clock.restart();
		// Process Events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// The 4 diagonal directions
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Numpad1)
				{// foreground moves towards lower left
					x_direction = -1;
					y_direction = 1;
					background.setPosition(0, 0);
					foreground.setPosition(0, 0);
				}
				else if (event.key.code == sf::Keyboard::Numpad3)
				{// foreground moves towards lower right
					x_direction = 1;
					y_direction = 1;
					background.setPosition(0, 0);
					foreground.setPosition(0, 0);
				}
				else if (event.key.code == sf::Keyboard::Numpad7)
				{// foreground moves towards upper left
					x_direction = -1;
					y_direction = -1;
					background.setPosition(0, 0);
					foreground.setPosition(0, 0);
				}
				else if (event.key.code == sf::Keyboard::Numpad9)
				{// foreground moves towards upper right
					x_direction = 1;
					y_direction = -1;
					background.setPosition(0, 0);
					foreground.setPosition(0, 0);
				}
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update
		foreground.move(sf::Vector2f(x_direction * speed * scale,
									 y_direction * speed * scale)
									 * deltaTime.asSeconds());
		if (foreground.getPosition().x * x_direction >= 64 * scale ||
			foreground.getPosition().y * y_direction >= 64 * scale)
			foreground.setPosition(0, 0);

		background.move(sf::Vector2f(x_direction * -speed * scale,
									 y_direction * -speed * scale)
									 * deltaTime.asSeconds());
		if ( -background.getPosition().x * x_direction >= 64 * scale || // Yes, I know this might short circuit, but just
			 -background.getPosition().y * y_direction >= 64 * scale)   // for the sake of clearness, I include both
			background.setPosition(0, 0);

		// Render
		window.clear();

		window.draw(background);
		window.draw(foreground);
		window.draw(dialogue);

		window.display();
	}

	return 0;
}
