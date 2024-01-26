#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "bat.h"
#include <sstream>
#include "ball.h"
using namespace sf;
int main()
{
    VideoMode vm1(1920, 1080);
    RenderWindow window(vm1, "Pong", Style::Fullscreen);
    int score = 0;
    int lives = 3;
    bool ballCollidedWithBat = false;
    bool isPaused = false;
    Bat bat(1920 / 2, 1080 - 20);
    Ball ball(1920 / 2, 0);
    Text hud;
    Font font;
    //"D:\VS Projects\Pong\fonts\DS-DIGIT.TTF"
    font.loadFromFile("fonts/DS-DIGIT.TTF");
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    // Start Screen.
    Text play;
    Font playFont;
    playFont.loadFromFile("fonts/DS-DIGIT.TTF");
    play.setFont(playFont);
    play.setCharacterSize(100);
    play.setFillColor(Color::Green);
    play.setPosition(310,300);

    Text end;
    Font endFont;
    endFont.loadFromFile("fonts/DS-DIGIT.TTF");
    end.setFont(endFont);
    end.setCharacterSize(100);
    end.setFillColor(Color::Red);
    end.setPosition(310, 700);
    
    Text gameOver;
    Font overFont;
    overFont.loadFromFile("fonts/DS-DIGIT.TTF");
    gameOver.setFont(overFont);
    gameOver.setCharacterSize(100);
    gameOver.setFillColor(Color::Blue);
    gameOver.setPosition(310, 500);

    //hit sound
    SoundBuffer hitSoundBuffer;
    hitSoundBuffer.loadFromFile("chop.wav");
    Sound hitSound;
    hitSound.setBuffer(hitSoundBuffer);
    hitSound.setVolume(300);

    //background sound
    SoundBuffer backgroundBuffer;
    backgroundBuffer.loadFromFile("background.wav");
    Sound background;
    background.setBuffer(backgroundBuffer);
    background.play();

    Clock clock;
    while (window.isOpen())
    {

        //Handling the player input
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            bat.moveLeft();
        }
        else
        {
            bat.stopLeft();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            bat.moveRight();
        }
        else
        {
            bat.stopRight();
        }
        //Update the bat ball and hud
        Time dt = clock.restart();
       
        std::stringstream ss;
        ss << "Score: " << score << "    Lives: " << lives;
        hud.setString(ss.str());
        
        std::stringstream sr;
        sr << "Press Enter To Play The Game";
        play.setString(sr.str());

        std::stringstream sd;
        sd << "Press Escape To End The Game";
        end.setString(sd.str());
        //Handle hitting the bottom
        if (ball.getPosition().top > window.getSize().y)
        {
            ball.reboundBottom();
            lives--;
            if (lives < 1)
            {
                score = 0;
                lives = 3;
                ball.resetSpeed();
                isPaused = false;
                
            }
        }
        //handling hitting the top
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();
        }
        //handling hitting side 
        if (ball.getPosition().left < 0 || (ball.getPosition().left + ball.getPosition().width) > window.getSize().x)
        {
            ball.reboundSides();
        }
        //handling bat and ball collisions
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            if (!ballCollidedWithBat)
            {
                hitSound.play();
                ball.reboundBatOrTop();
                score++;
                ballCollidedWithBat = true;
            }
        }
        else
        {
            ballCollidedWithBat = false;
        }
        //handle bat hitting sides
        if (bat.getPosition().left + bat.getPosition().width < 0)
        {
            bat.batTouchLeft();
        }
        if (bat.getPosition().left > 1920)
        {
            bat.batTouchRight();
        }
        //(bat.getPosition().left + bat.getPosition().width > window.getSize().x)
        //draw the bat ball and hud
        window.clear();
        window.draw(hud);
        if (!isPaused)
        {
            window.draw(play);
            window.draw(end);
            if (Keyboard::isKeyPressed(Keyboard::Enter))
            {
                isPaused = true;
                lives = 3;
            }
        }
        if (isPaused)
        {
            bat.update(dt);
            ball.update(dt);
            window.draw(bat.getShape());
            window.draw(ball.getShape());
        }
        window.display();
    }
    return 0;
}
