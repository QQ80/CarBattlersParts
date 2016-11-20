#include <SFML/Graphics.hpp>
#include <string>

class App
{
    const   unsigned            window_width        {240u};
    const   unsigned            window_height       {160u};
    const   unsigned            scale               {2u};
    const   float               speed               {15.f};
    const   float               scaledSpeed         {speed * scale};
    const   sf::VideoMode       vidMode             {window_width * scale,
                                                    window_height * scale};
    const   sf::Time            TimePerFrame        {sf::seconds(1.f / 60.f)};

  public:
                                App                 ()
    {
        mBackgroundTexture.loadFromFile("Media/Machinesbgpink.png");// muahahah real men don't handle errorsss
        mBackgroundTexture.setRepeated(true);
        mBackgroundTexture.setSmooth(true);

        mForegroundTexture.loadFromFile("Media/Machinesfgpink.png");
        mForegroundTexture.setRepeated(true);

        mDialogueBoxTexture.loadFromFile("Media/DialogueBox.png");

        // Get (64+240+64)*(64+160+64) of texture
        const sf::IntRect textureRect{0, 0, 368, 288};

        mBackground.setTextureRect(textureRect);
        mBackground.setOrigin(64, 64);
        mBackground.scale(scale, scale);

        mForeground.setTextureRect(textureRect);
        mForeground.setOrigin(64, 64);
        mForeground.scale(scale, scale);

        mDialogueBox.setTextureRect(sf::IntRect(0, 0, 176, 72));
        mDialogueBox.setPosition(32 * scale, 70 * scale) ;
        mDialogueBox.scale(scale, scale);
    }
            void                run                 ()
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
  private:
            void                processEvents       ()
    {
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
            // The 4 diagonal directions
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                  case sf::Keyboard::Numpad1:
                    mUnitMovement = sf::Vector2i(-1, +1); break;
                  case sf::Keyboard::Numpad3:
                    mUnitMovement = sf::Vector2i(+1, +1); break;
                  case sf::Keyboard::Numpad7:
                    mUnitMovement = sf::Vector2i(-1, -1); break;
                  case sf::Keyboard::Numpad9:
                    mUnitMovement = sf::Vector2i(+1, -1); break;
                  default:
                    mUnitMovement = sf::Vector2i( 0,  0);
                }
                mMovement = sf::Vector2f(mUnitMovement) * scaledSpeed;
                resetBackground();
            }
            if (event.type == sf::Event::Closed)
                mWindow.close();
        }
    }
            void                update              (sf::Time deltaTime)
    {
        const float Xdisplaced = mForeground.getPosition().x * mUnitMovement.x;
        if (Xdisplaced > 64.f * scale)
        {
            resetBackground();
            return;
        }
        const sf::Vector2f mov = mMovement * deltaTime.asSeconds();
        mForeground.move( mov);
        mBackground.move(-mov);
    }
            void                render              ()
    {
        mWindow.clear();

        mWindow.draw(mBackground);
        mWindow.draw(mForeground);
        mWindow.draw(mDialogueBox);

        mWindow.display();
    }
            void                resetBackground     ()
    {
        mBackground.setPosition(0, 0);
        mForeground.setPosition(0, 0);
    }
  private:
            sf::RenderWindow    mWindow             {vidMode, "Yay GBA!"};
            sf::Texture         mBackgroundTexture;
            sf::Texture         mForegroundTexture;
            sf::Texture         mDialogueBoxTexture;
            sf::Sprite          mBackground         {mBackgroundTexture};
            sf::Sprite          mForeground         {mForegroundTexture};
            sf::Sprite          mDialogueBox        {mDialogueBoxTexture};
            sf::Vector2i        mUnitMovement       {1, 1};
            sf::Vector2f        mMovement           {scaledSpeed, scaledSpeed};
};

int main()
{
    App app;
    app.run();

    return 0;
}

