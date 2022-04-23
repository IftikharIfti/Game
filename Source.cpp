#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <string>
#include <conio.h>
#include "Ark.h"
#include "pong++.h"

using namespace sf;
using namespace std;

void choose();
void  game_option();

int  main()
{
	RenderWindow menu(VideoMode(800, 600), "Menu");

	//Sprite
	Texture t;
	t.loadFromFile("Menu_bg.jpg");
	Sprite background(t);
	menu.setFramerateLimit(9);

	//text
	Font  fnt, fnt1;
	fnt.loadFromFile("ApeMount-WyPM9.ttf");
	fnt1.loadFromFile("Doreking-3BYZ.ttf");

	//menu option
	Text header, start, option, exit;

	//header
	header.setFont(fnt1);
	header.setString("Pad_Lock");
	header.setFillColor(Color::Red);
	header.setCharacterSize(70);
	header.setPosition(250, 20);

	//start
	start.setFont(fnt);
	start.setString("Start");
	start.setFillColor(Color::Red);
	start.setCharacterSize(30);
	start.setPosition(330, 200);

	//option
	option.setFont(fnt);
	option.setString("Instruction");
	option.setFillColor(Color::White);
	option.setCharacterSize(30);
	option.setPosition(330, 240);

	//exit
	exit.setFont(fnt);
	exit.setString("exit");
	exit.setFillColor(Color::White);
	exit.setCharacterSize(30);
	exit.setPosition(330, 280);

	int cnt = 0;
	while (menu.isOpen())
	{

		Event e;
		while (menu.pollEvent(e))
		{
			if (e.type == Event::Closed)
				menu.close();
		}


		menu.clear();
		menu.draw(background);
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			cnt++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			cnt--;
		}
		if (cnt > 2)
		{
			cnt = 0;
		}
		if (cnt < 0)
			cnt = 2;

		if (cnt == 1)
		{
			start.setFillColor(Color::White);
			option.setFillColor(Color::Red);
			exit.setFillColor(Color::White);
		}

		if (cnt == 2)
		{
			start.setFillColor(Color::White);
			option.setFillColor(Color::White);
			exit.setFillColor(Color::Red);
		}
		if (cnt == 0)
		{
			start.setFillColor(Color::Red);
			option.setFillColor(Color::White);
			exit.setFillColor(Color::White);
		}
		if (Keyboard::isKeyPressed(Keyboard::Enter))
		{
			if (cnt == 0)
				choose();
			if (cnt == 1)
				game_option();
			if (cnt == 2)
				menu.close();

		}
		menu.draw(header);
		menu.draw(start);
		menu.draw(option);
		menu.draw(exit);
		menu.display();


	}

}

void choose()
{
	RenderWindow choose(VideoMode(800, 600), "Menu");
	Texture t;
	t.loadFromFile("Menu_bg.jpg");
	Sprite background(t);
	choose.setFramerateLimit(9);
	//text
	Font  fnt;
	fnt.loadFromFile("ApeMount-WyPM9.ttf");
	//menu option
	Text start, option, exit, inst;
	//start
	start.setFont(fnt);
	start.setString("Single Player");
	start.setFillColor(Color::Red);
	start.setCharacterSize(30);
	start.setPosition(200, 200);

	//option
	option.setFont(fnt);
	option.setString("Multiplayer");
	option.setFillColor(Color::White);
	option.setCharacterSize(30);
	option.setPosition(200, 240);

	//exit
	exit.setFont(fnt);
	exit.setString("Back");
	exit.setFillColor(Color::White);
	exit.setCharacterSize(30);
	exit.setPosition(200, 280);

	//instruction
	inst.setFont(fnt);
	inst.setString("Press F to enter");
	inst.setFillColor(Color::White);
	inst.setCharacterSize(30);
	inst.setPosition(200, 380);

	int cnt = 0;
	while (choose.isOpen())
	{

		Event e;
		while (choose.pollEvent(e))
		{
			if (e.type == Event::Closed)
				choose.close();
		}


		choose.clear();
		choose.draw(background);
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			cnt++;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{

			cnt--;
		}
		if (cnt > 2)
		{
			cnt = 0;
		}
		if (cnt < 0)
			cnt = 2;

		if (cnt == 1)
		{
			start.setFillColor(Color::White);
			option.setFillColor(Color::Red);
			exit.setFillColor(Color::White);
		}
		if (cnt == 2)
		{
			start.setFillColor(Color::White);
			option.setFillColor(Color::White);
			exit.setFillColor(Color::Red);
		}
		if (cnt == 0)
		{
			start.setFillColor(Color::Red);
			option.setFillColor(Color::White);
			exit.setFillColor(Color::White);
		}
		if (Keyboard::isKeyPressed(Keyboard::F))
		{
			if (cnt == 0)
			{
				ark();
				choose.close();
			}
			if (cnt == 1) {
				pong();
			}
			if (cnt == 2)
				choose.close();

		}

		choose.draw(start);
		choose.draw(option);
		choose.draw(exit);
		choose.draw(inst);
		choose.display();

	}

}
void game_option()
{
	RenderWindow inst(VideoMode(800, 600), "Menu");
	Texture t;
	t.loadFromFile("inst.jpg");
	Sprite background(t);
	while (inst.isOpen())
	{

		Event e;
		while (inst.pollEvent(e))
		{
			if (e.type == Event::Closed)
				inst.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{

				inst.close();
			}
		}


		inst.clear();
		inst.draw(background);
		inst.display();
	}
}