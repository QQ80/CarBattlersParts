#include <SFML/Graphics.hpp>
#include <string>
namespace
{
    const int           window_width            = 240;
    const int           window_height           = 160;
    const float         speed                   = 15.f;
    const int           scale                   = 2;
    const float         scaledSpeed             = speed * scale;
    const sf::VideoMode vidMode                 {window_width * scale,
                                                window_height * scale};
    const sf::Time      TimePerFrame            = sf::seconds(1.f / 60.f);
}

class App
{
  public:
                        App                     ();
    void                run                     ();
  private:
    void                processEvents           ();
    void                update                  (sf::Time deltaTime);
    void                render                  ();
    void                resetBackground         ();
  private:
    sf::RenderWindow    mWindow                 {vidMode, "Yay GBA!"};
    sf::Texture         mBackgroundTexture;
    sf::Texture         mForegroundTexture;
    sf::Texture         mDialogueBoxTexture;
    sf::Sprite          mBackground             {mBackgroundTexture};
    sf::Sprite          mForeground             {mForegroundTexture};
    sf::Sprite          mDialogueBox            {mDialogueBoxTexture};
    sf::Vector2f        mMovement               {scaledSpeed, scaledSpeed};
};

App::App()
{
    auto setupTexture = [](sf::Texture& text,
                           std::string  filePath,
                           bool         setRepeated = false,
                           bool         setSmooth   = false)
    {
        text.loadFromFile(filePath); // muahahah real men don't handle errorsss (They strong-arm users to leave the file alone)
        text.setRepeated(setRepeated);
        text.setSmooth(setSmooth);
    };
    setupTexture(mBackgroundTexture,  "Media/Machinesbgpink.png", true, true);
    setupTexture(mForegroundTexture,  "Media/Machinesfgpink.png", true);
    setupTexture(mDialogueBoxTexture, "Media/DialogueBox.png");

    // Get (64+240+64)*(64+160+64) of texture
    const sf::IntRect textureRec{0, 0, 368, 288};
    auto setupSprite = [&](sf::Sprite& sprite)
    {
        sprite.setTextureRect(textureRec);
        sprite.setOrigin(64, 64);
        sprite.scale(scale, scale);
        //sprite.setPosition(0, 0); (implied)
    };
    setupSprite(mBackground);
    setupSprite(mForeground);

    mDialogueBox.setTextureRect(sf::IntRect(0, 0, 176, 72));
    mDialogueBox.setPosition(32 * scale, 70 * scale) ;
    mDialogueBox.scale(scale, scale);
}

void App::run()
{
    // Main loop
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
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
    while (mWindow.pollEvent(event))
    {
        // The 4 diagonal directions
        if (event.type == sf::Event::KeyPressed)
        {
            if      (event.key.code == sf::Keyboard::Numpad1)
                mMovement = sf::Vector2f(-1.f, +1.f) * scaledSpeed;
            else if (event.key.code == sf::Keyboard::Numpad3)
                mMovement = sf::Vector2f(+1.f, +1.f) * scaledSpeed;
            else if (event.key.code == sf::Keyboard::Numpad7)
                mMovement = sf::Vector2f(-1.f, -1.f) * scaledSpeed;
            else if (event.key.code == sf::Keyboard::Numpad9)
                mMovement = sf::Vector2f(+1.f, -1.f) * scaledSpeed;
            else
                mMovement = sf::Vector2f( 0.f,  0.f);
            resetBackground();
        }
        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void App::update(sf::Time deltaTime)
{
    const sf::Vector2f mov = mMovement * deltaTime.asSeconds();
    mForeground.move( mov);
    mBackground.move(-mov);

    const sf::Vector2f unitMovement = mMovement / scaledSpeed;
    const float Xdisplaced = mForeground.getPosition().x * unitMovement.x;
    if (Xdisplaced >= 64.f * scale) resetBackground();
    /*
    const float Ydisplaced = mForeground.getPosition().y * unitMovement.y;
    if      (+Xdisplaced >= 64.f * scale)
    {
        mov = sf::Vector2f(-64.f * scale, 0);
        mForeground.move( mov);
        mBackground.move(-mov);
    }
    else if (+Ydisplaced >= 64.f * scale)
    {
        mov = sf::Vector2f(0, -64.f * scale);
        mForeground.move( mov);
        mBackground.move(-mov);
    }
    else if (-Xdisplaced >= 64.f * scale)
    {
        mov = sf::Vector2f(64.f * scale, 0);
        mForeground.move( mov);
        mBackground.move(-mov);
    }
    else if (-Ydisplaced >= 64.f * scale)
    {
        mov = sf::Vector2f(0, 64.f * scale);
        mForeground.move( mov);
        mBackground.move(-mov);
    }
    */
}

void App::render()
{
    mWindow.clear();

    mWindow.draw(mBackground);
    mWindow.draw(mForeground);
    mWindow.draw(mDialogueBox);

    mWindow.display();
}

void App::resetBackground()
{
    mForeground.setPosition(0, 0);
    mBackground.setPosition(0, 0);
}

int main()
{
    App app;
    app.run();

    return 0;
}

