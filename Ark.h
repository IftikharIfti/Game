#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<time.h>
#include<string>
#define x_speed 6;
#define y_speed 5;
int score1 = 10;
using namespace sf;

bool Collision(Sprite s1, Sprite s2);
int gameonpause();
void playerlose();
void playerwins();

void  ark()
{
	//Creating the window:
	srand(time(0));
	RenderWindow window(VideoMode(800, 600), "Arkanoid Game!", Style::Default);
	window.setFramerateLimit(60);
	//Textures:
	Texture tex1, tex2, tex3, tex4, tex5, tex6, tex7, tex8, tex9;
	tex1.loadFromFile("Background ark.jpg");
	tex2.loadFromFile("Ball3.png");
	tex3.loadFromFile("Paddle_ark.png");
	tex4.loadFromFile("Block.png");
	tex5.loadFromFile("Paddle_large.png");
	tex6.loadFromFile("Extender.png");
	tex7.loadFromFile("Faster.png");
	tex8.loadFromFile("Reducer.png");
	tex9.loadFromFile("Paddle_small.png");


	//Sound Buffers:
	SoundBuffer buffer, buffer1, buffer2;
	buffer.loadFromFile("Ball_Block.wav");
	buffer1.loadFromFile("Ball_Paddle.wav");
	buffer2.loadFromFile("powerups.wav");

	//Loading Sound Buffers:
	Sound Bsound, Psound, Powsound;
	Bsound.setBuffer(buffer);
	Psound.setBuffer(buffer1);
	Powsound.setBuffer(buffer2);

	//Scoring:

	Font font;
	font.loadFromFile("ApeMount-WyPM9.ttf");
	Text Score1;
	Score1.setCharacterSize(15);
	Score1.setPosition(2, 3);
	Score1.setFont(font);
	Score1.setString(" Lives Count : " + std::to_string(score1));

	//Creating and initializing Sprites:
	Sprite Bg(tex1), Ball(tex2), SPaddle(tex3), LPaddle(tex5), Extender(tex6), Paddle, Faster(tex7), Reducer(tex8), SSPaddle(tex9);
	Paddle = SPaddle;
	Paddle.setPosition(400, 570);
	Ball.setPosition(400, 500);
	Extender.setPosition(-100, 0);
	Reducer.setPosition(-100, 0);
	Faster.setPosition(-100, 0);
	LPaddle.setPosition(370, 570);
	SSPaddle.setPosition(370, 570);
	int paddlelen = 74;


	Sprite Block[1000];
	int n = 0;
	for (int i = 1; i <= 23; i++)
		for (int j = 2; j <= 11; j++)
		{
			Block[n].setTexture(tex4);
			Block[n].setPosition(i * 32, j * 17);
			n++;
		}
	//BallSpeed:
	float dx = x_speed;
	float dy = y_speed;

	//Main Loop:
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			}
		}

		//Moving the ball:
		Ball.move(dx, 0);
		for (int i = 0; i < n; i++)
			if (Collision(Ball, Block[i]))
			{
				Block[i].setPosition(-100, 0);
				Bsound.play();
				dx = -dx;
				if (i % 2 == 0 && Extender.getPosition().x < 0)
				{
					Extender.setPosition(400, 100);

				}
				if (i % 3 == 0 && Reducer.getPosition().x < 0)
				{
					Reducer.setPosition(500, 100);

				}
				if (i % 5 == 0 && Faster.getPosition().x < 0)
				{
					Faster.setPosition(300, 100);

				}

			}
		Ball.move(0, dy);
		for (int i = 0; i < n; i++)
			if (Collision(Ball, Block[i]))
			{
				Block[i].setPosition(-100, 0);
				Bsound.play();
				dy = -dy;

			}


		Vector2f vect = Ball.getPosition();
		if (vect.x < 0 || vect.x>800 - 24) dx = -dx;
		if (vect.y < 0 || vect.y>600) dy = -dy;
		if (vect.y > 600)
		{
			Score1.setString(" Lives Count : " + std::to_string(score1));
			Paddle.setPosition(400, 570);
			Ball.setPosition(400, 500);
			Paddle = SPaddle;
			paddlelen = 74;
			dx = 6;
			dy = 5;

		}
		//Powerups:
		Extender.move(0, 3);
		if (Collision(Extender, Paddle))
		{
			Extender.setPosition(-100, 0);
			Powsound.play();
			Paddle = LPaddle;
			paddlelen = 118;

		}

		Reducer.move(0, 3);
		if (Collision(Reducer, Paddle))
		{
			Reducer.setPosition(-100, 0);
			Powsound.play();
			Paddle = SSPaddle;
			paddlelen = 59;

		}

		Faster.move(0, 3);
		if (Collision(Faster, Paddle))
		{
			Faster.setPosition(-100, 0);
			Powsound.play();
			dx = dx + 2;
			dy = dy + 2;
		}
		//Reset:
		if (vect.y > 600)
		{
			score1--;
			Score1.setString(" Lives Count : " + std::to_string(score1));
			Paddle.setPosition(400, 570);
			Ball.setPosition(400, 500);
			dx = 6;
			dy = 5;
		}

		//PaddleMovement:
		Vector2f vect2 = Paddle.getPosition();
		if (Keyboard::isKeyPressed(Keyboard::Left) && vect2.x > 0)Paddle.move(-6, 0);
		if (Keyboard::isKeyPressed(Keyboard::Right) && vect2.x < 800 - paddlelen)Paddle.move(6, 0);

		if (Collision(Paddle, Ball))
		{
			dy = -(rand() % 5 + 1);
			Psound.play();
		}
		//Pausing the Game:
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			int output = gameonpause();
			if (output == 1)
				window.close();
		}
		//Game Over:
		if (score1 == 0)
		{
			playerlose();
			window.close();

		}
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			if (Block[i].getPosition().x > 0)
			{
				count++;

			}
		}
		if (count == 0)
		{
			playerwins();
			window.close();
		}
		//Drawings:
		window.clear();
		window.draw(Bg);
		window.draw(Ball);
		window.draw(Paddle);
		window.draw(Score1);
		window.draw(Extender);
		window.draw(Faster);
		window.draw(Reducer);

		for (int i = 0; i < n; i++)
			window.draw(Block[i]);
		window.display();
	}

	
}
bool Collision(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}

int  gameonpause()
{
	RenderWindow window1(VideoMode(800, 600), "Arkanoid!");
	Texture t10;
	t10.loadFromFile("pause_updated.jpg");
	Sprite sGamepause(t10);
	while (window1.isOpen())
	{
		Event f;
		while (window1.pollEvent(f))
		{
			if (f.type == Event::Closed)
				window1.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			return 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window1.close();
		}

		window1.clear();
		window1.draw(sGamepause);
		window1.display();
	}
}
void playerlose()
{
	RenderWindow app1(VideoMode(800, 600), "Arkanoid!");
	Texture t11;
	t11.loadFromFile("Gameover.jpg");
	Sprite sGameover(t11);
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
void playerwins()
{
	RenderWindow app1(VideoMode(800, 600), "Arkanoid!");
	Texture t11;
	t11.loadFromFile("win.jpg");
	Sprite sGameover(t11);
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
