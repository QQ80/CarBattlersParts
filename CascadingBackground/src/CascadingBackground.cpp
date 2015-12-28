#include <SFML/Graphics.hpp>

const int window_width = 240;
const int window_height = 160;
const float speed = 15.f;
const int scale = 4;
const sf::VideoMode vidMode{window_width * scale, window_height * scale};
const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

class App
{
public:
    App();
    void run();
private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void resetBackground();
private:
    sf::RenderWindow m_window;
    sf::Texture m_bgTex; // Background back
    sf::Texture m_fgTex; // Background front
    sf::Texture m_dgTex; // Dialogue Box
    sf::Sprite m_bg;
    sf::Sprite m_fg;
    sf::Sprite m_dg;
    sf::Vector2i m_movement;
};

App::App()
: m_window(vidMode, "Yay GBA!")
, m_bgTex()
, m_fgTex()
, m_dgTex()
, m_bg(m_bgTex)
, m_fg(m_fgTex)
, m_dg()
, m_movement(1, -1)
{
    m_bgTex.loadFromFile("Media/Machinesbgpink.png"); //muahahah real men dont handle errorsssss
	m_bgTex.setRepeated(true);
	m_bgTex.setSmooth(true);

	m_fgTex.loadFromFile("Media/Machinesfgpink.png");
	m_fgTex.setRepeated(true);
	//m_fgTex.setSmooth(true);

	m_dgTex.loadFromFile("Media/DialogueBox.png");

	m_bg.setTextureRect(sf::IntRect(0, 0, 368, 288)); // Get (64+240+64)x(64+160+64) of texture
	m_bg.setOrigin(64, 64);
	m_bg.scale(scale, scale);
	//m_bg.setPosition(0, 0); //implied

	m_fg.setTextureRect(sf::IntRect(0, 0, 368, 288));
	m_fg.setOrigin(64, 64);
	m_fg.scale(scale, scale);
	//m_fg.setPosition(0, 0); //implied

    m_dg.setTexture(m_dgTex);
	m_dg.setPosition(32 * scale, 70 * scale) ;
	m_dg.scale(scale, scale);
}

void App::run()
{
    // Main loop
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero; //lol temp solution for now
	while (m_window.isOpen())
	{
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
        }
        render();
	}
}

void App::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // The 4 diagonal directions
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Numpad1)
            {// foreground moves towards lower left
                m_movement = sf::Vector2i(-1, 1);
                resetBackground();
            }
            else if (event.key.code == sf::Keyboard::Numpad3)
            {// foreground moves towards lower right
                m_movement = sf::Vector2i(1, 1);
                resetBackground();
            }
            else if (event.key.code == sf::Keyboard::Numpad7)
            {// foreground moves towards upper left
                m_movement = sf::Vector2i(-1, -1);
                resetBackground();
            }
            else if (event.key.code == sf::Keyboard::Numpad9)
            {// foreground moves towards upper right
                m_movement = sf::Vector2i(1, -1);
                resetBackground();
            }
        }

        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}

void App::update(sf::Time deltaTime)
{
    auto mov = sf::Vector2f(m_movement * scale) * speed * deltaTime.asSeconds();
    m_fg.move(mov);
    m_bg.move(-mov);
    if (m_fg.getPosition().x * m_movement.x >= 64 * scale)
        resetBackground();
    /*
    if (m_fg.getPosition().x * m_movement.x >= 64 * scale ||
        m_fg.getPosition().y * m_movement.y >= 64 * scale)
        m_fg.setPosition(0, 0);

    m_bg.move(m_movement * -speed * scale * deltaTime.asSeconds());
    if ( -m_bg.getPosition().x * m_movement.x >= 64 * scale ||
         -m_bg.getPosition().y * m_movement.y >= 64 * scale)
        m_bg.setPosition(0, 0);
    */
}

void App::render()
{
    m_window.clear();

    m_window.draw(m_bg);
    m_window.draw(m_fg);
    m_window.draw(m_dg);

    m_window.display();
}

void App::resetBackground()
{
    m_fg.setPosition(0, 0);
    m_bg.setPosition(0, 0);
}

int main()
{
    App app;
    app.run();

	return 0;
}
