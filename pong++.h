#ifndef PONG_H
#define PONG_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include<iostream>
#include<string>
#include<SFML/Audio.hpp>
int scoree1 = 0, score2 = 0;
using namespace sf;
using namespace std;
void player1win();
void player2win();
int  gamepongpause(int flag);
void gamepongover()
{
    RenderWindow app1(VideoMode(520, 450), "Arkanoid!");
    Texture t5;
    t5.loadFromFile("9.jpg");
    Sprite sGameover(t5);
    while (app1.isOpen())
    {
        Event f;
        while (app1.pollEvent(f))
        {
            if (f.type == Event::Closed)
                app1.close();
        }
        app1.clear();
        app1.draw(sGameover);
        app1.display();
    }

}
void pong()
{
    RenderWindow app(VideoMode(735,490 ), "PONG!");
   
    app.setFramerateLimit(60);
    SoundBuffer buffer;
    buffer.loadFromFile("mixkit-light-impact-on-the-ground-2070.wav");
    Sound sound;
    sound.setBuffer(buffer);
    //texture input
    Texture t1, t2, t3, t4,t5;
    t1.loadFromFile("block01.png");
    t2.loadFromFile("pong_bg.jpg");
    t3.loadFromFile("ball.png");
    t4.loadFromFile("Paddle_large_pong.png");
    t5.loadFromFile("gamepause.jpg");

    //texture creation
    Sprite sBackground(t2), sBall(t3), sPaddle1(t4),sPaddle2(t4),sPause(t5);
    //ball paddles info
    Vector2f ballposition(300, 350);
    sPaddle1.setPosition(254, 475);
    sPaddle2.setPosition(254, 1);
    sBall.setPosition(ballposition);
    float xvelocity = 3;
    float yvelocity = 3;
    Sprite block[1000];

    //score
    Font fnt;
    fnt.loadFromFile("ApeMount-WyPM9.ttf");


    Text Score1;
    Score1.setCharacterSize(15);
    Score1.setPosition(2, 3);
    Score1.setFont(fnt);
    Score1.setString(" P1 Score: " + to_string(scoree1));

    Text Score2;
    Score2.setCharacterSize(15);
    Score2.setPosition(600, 3);
    Score2.setFont(fnt);
    Score2.setString("P2 Score: " + to_string(scoree1));

    int collision = 0;
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

            if (ballposition.x < 0 || ballposition.x>735 - 12) xvelocity *= -1;
            if (ballposition.y > 490)
            {
                collision = 0;
                xvelocity = 3;
                yvelocity = 3;
                scoree1++;
                Score1.setString("P1 Score: " + to_string(scoree1));
                ballposition.x = 300;
                ballposition.y = 100;
                sPaddle1.setPosition(254, 475);
                sPaddle2.setPosition(254, 1);
            }
            if (ballposition.y < 0)
            {
                collision = 0;
                xvelocity = -3;
                yvelocity = -3;
                score2++;
                Score2.setString("P2 Score: " + to_string(score2));
                ballposition.x = 300;
                ballposition.y = 400;
                sPaddle1.setPosition(254, 475);
                sPaddle2.setPosition(254, 1);
            }
            //if (ballposition.y < 0) yvelocity *= -1;
            if (collision == 3)
            {
                xvelocity=6; yvelocity=6;
            }
            if (collision == 7)
            {
                xvelocity=15; yvelocity=15;
            }
            ballposition.x += xvelocity;
            ballposition.y += yvelocity;
            sBall.setPosition(ballposition);

            //paddle 1 movement
            if (Keyboard::isKeyPressed(Keyboard::Right) && sPaddle1.getPosition().x < (735 - 100)) { sPaddle1.move(8, 0); }
            if (Keyboard::isKeyPressed(Keyboard::Left) && sPaddle1.getPosition().x > 0) sPaddle1.move(-8, 0);
            //paddle 2 movement
            if (Keyboard::isKeyPressed(Keyboard::D) && sPaddle2.getPosition().x < (735 - 100)) { sPaddle2.move(8, 0); }
            if (Keyboard::isKeyPressed(Keyboard::A) && sPaddle2.getPosition().x > 0) sPaddle2.move(-8, 0);
            
            if (sBall.getGlobalBounds().intersects(sPaddle1.getGlobalBounds())) {
                collision++;
                sound.play();
                yvelocity = -(rand() % 5 + 3);
            }
            if (sBall.getGlobalBounds().intersects(sPaddle2.getGlobalBounds())) {
               
                sound.play();
                yvelocity = (rand() % 5 + 3);
            }
          
            if (scoree1 == 3)
            {
                player1win();
                app.close();
            }
            else if (score2 == 3)
            {
                player2win();
                app.close();
            }
            int cnt = 0;
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                
               int output= gamepongpause(cnt);
            
               
                if (output == 1)
                    app.close();

            }
            app.clear();
            app.draw(sBackground);
            app.draw(sBall);
            app.draw(Score1);
            app.draw(Score2);
            app.draw(sPaddle1);
            app.draw(sPaddle2);

            app.display();
        
    }


}
void player1win()
{
    RenderWindow app1(VideoMode(735, 490), "Arkanoid!");
    Texture t5;
    t5.loadFromFile("winner-1.png");
    Sprite sGameover(t5);
    while (app1.isOpen())
    {
        Event f;
        while (app1.pollEvent(f))
        {
            if (f.type == Event::Closed)
                app1.close();
        }
        app1.clear();
        app1.draw(sGameover);
        app1.display();
    }
}
void player2win()
{
    RenderWindow app1(VideoMode(735, 490), "Arkanoid!");
    Texture t6;
    t6.loadFromFile("winner-2.png");
    Sprite sGameover(t6);
    while (app1.isOpen())
    {
        Event f;
        while (app1.pollEvent(f))
        {
            if (f.type == Event::Closed)
                app1.close();
        }
        app1.clear();
        app1.draw(sGameover);
        app1.display();
    }
}
int  gamepongpause(int cnt)
{
    RenderWindow app1(VideoMode(520, 450), "Arkanoid!");
    Texture t5;
    t5.loadFromFile("gamepause.jpg");
    Sprite sPause(t5);
    app1.setFramerateLimit(10);
    Font  fnt;
    fnt.loadFromFile("ApeMount-WyPM9.ttf");
    //menu option
    Text start, option, exit;
    //start
    start.setFont(fnt);
    start.setString("Continue");
    start.setFillColor(Color::Red);
    start.setCharacterSize(30);
    start.setPosition(200, 150);

    //exit
    exit.setFont(fnt);
    exit.setString("exit");
    exit.setFillColor(Color::White);
    exit.setCharacterSize(30);
    exit.setPosition(230, 280);
    while (app1.isOpen())
    {
        Event f;
        while (app1.pollEvent(f))
        {
            if (f.type == Event::Closed)
                app1.close();
        }

        app1.clear();
        app1.draw(sPause);
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            cnt++;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            cnt--;
        }
        
        if (cnt > 1)
        {
            cnt = 0;
        }
        if (cnt < 0)
            cnt = 1;

        if (cnt == 1)
        {
            start.setFillColor(Color::White);
            exit.setFillColor(Color::Red);
            
        }
        if (cnt == 0)
        {
            start.setFillColor(Color::Red);
            exit.setFillColor(Color::White);
        }
        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            if (cnt == 0)
                app1.close();
            if (cnt == 1)
            {
                return 1;
                app1.close();
            }

        }
        app1.draw(start);
        app1.draw(exit);
        app1.display();
    }
}
#endif