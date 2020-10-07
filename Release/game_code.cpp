#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <string>
#include<sstream>
#include"Map.h"
#include"Camera.h"
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( once: 4996 )
#endif
using namespace sf;
using namespace std;
class Entity
{
public:
	float dx, dy, x, y, speed, moveTimer;
	int health, w, h, x0,y0;
	bool life;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, float X, float Y, int X0,int Y0,int W, int H, string Name)
	{
		x = X; y = Y; h = H; w = W; name = Name; moveTimer = 0;
		x0 = X0; y0 = Y0;
		speed = 0; health = 100; 
		dx = 0; dy = 0; life = true;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};
class Player :
public Entity
{
public:
	int  playerScore;
	enum { left, right, up, down }state;
	Player(Image &image, float X, float Y,int X0,int Y0, int W, int H, string Name):Entity(image,X,Y,X0,Y0,W,H,Name)
	{
		playerScore = 0; 
		sprite.setTextureRect(IntRect(X0,Y0, W, H));
	}
	void update(float *ptime)
	{
		controlFunc();
		switch (state)
		{
		case right:dx = speed; dy = 0; break;
		case left:dx = -speed; dy = 0; break;
		case down:dx = 0; dy = speed; break;
		case up:dx = 0; dy = -speed; break;
		}
		x += dx * (*ptime);
		y += dy * (*ptime);
		speed = 0;
		sprite.setPosition(x, y);
		InteractionWithMap();
		if (health <= 0)
		{
			life = false;
			speed = 0;
		}
		if (life) 
		{
			getPlayerCoordinateForView(x, y);
		}
	}
	void InteractionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
		{
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == 'b')
				{
					if (dy > 0)
					{
						y = i * 32 - h;
					}
					if (dy < 0)
					{
						y = i * 32 + h;
					}
					if (dx > 0)
					{
						x = j * 32 - w;
					}
					if (dx < 0)
					{
						x = j * 32 + w;
					}
				}
				if (TileMap[i][j] == 'r')
				{
					TileMap[i][j] = 'l';
					playerScore++;
				}
				if (TileMap[i][j] == 'd')
				{
					health -= 10;
					TileMap[i][j] = 'l';
				}
			}
		}
	}
	void controlFunc()
	{
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			state = up; speed = 0.2;
			getPlayerCoordinateForView(getPlayerPositionX(), getPlayerPositionY());
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			state = down; speed = 0.2;
			getPlayerCoordinateForView(getPlayerPositionX(), getPlayerPositionY());
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			state = right; speed = 0.2;
			getPlayerCoordinateForView(getPlayerPositionX(), getPlayerPositionY());
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			state = left; speed = 0.2;
			getPlayerCoordinateForView(getPlayerPositionX(), getPlayerPositionY());
		}
	}
	void animationFunc(float *pCurrentFrame,float *ptime)
	{
		*pCurrentFrame += *ptime * 0.005;
		if (*pCurrentFrame > 3)
			*pCurrentFrame -= 3;
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			sprite.setTextureRect(IntRect(32 * int(*pCurrentFrame), 96, 32, 32));
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
		   sprite.setTextureRect(IntRect(32 * int(*pCurrentFrame), 0, 32, 32));
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			sprite.setTextureRect(IntRect(32 * int(*pCurrentFrame), 64, 32, 32));
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			sprite.setTextureRect(IntRect(32 * int(*pCurrentFrame), 32, 32, 32));
		}
	}
	float getPlayerPositionX()
	{
		return x;
	}
	float getPlayerPositionY()
	{
		return y;
	}
};
class Enemy :
public Entity
{
public:
	Enemy(Image &image, float X, float Y,int X0,int Y0, int W, int H, string Name) :Entity(image, X, Y,X0,Y0, W, H, Name)
	{
		sprite.setTextureRect(IntRect(X0,Y0,W,H));
		dx = 0.1;
	}
	void InteractionWithMap()
	{
		for (int i = y / 32; i < (y + h) / 32; i++)
			for (int j = x / 32; j < (x + w) / 32; j++)
			{
				if (TileMap[i][j] == 'b')
				{
					if (dy > 0)
					{
						y = i * 32 - h;
					}
					if (dy < 0)
					{
						y = i * 32 + h;
					}
					if (dx > 0)
					{
						x = j * 32 - w;
					}
					if (dx < 0)
					{
						x = j * 32 + w;
					}
				}
			}
	}
	void update(float *ptime)
	{
		moveTimer += *ptime;
		if (moveTimer > 2000)
		{
			dx *= -1;
			moveTimer = 0;
		}
		InteractionWithMap();
		x += dx * *ptime;
		sprite.setPosition(x, y);
		if (health <= 0)
		{
			life = false;
		}
	}
	void animationFunc(float *pCurrentFrame,float *ptime)
	{
		*pCurrentFrame += *ptime * 0.005;
		if (*pCurrentFrame > 3)
			*pCurrentFrame -= 3;
		if (dx > 0)
		{
			sprite.setTextureRect(IntRect(32 * int(*pCurrentFrame), 129, 32, 32));
		}
		if (dy < 0)
		{
			sprite.setTextureRect(IntRect(32 * int(*pCurrentFrame), 161, 32, 32));
		}
	}
};
int main()
{
	RenderWindow window(VideoMode(1920, 1080), "Game", Style::Fullscreen);
	window.setFramerateLimit(30);
	view.reset(FloatRect(0, 0, 960, 540));

	//Music music_main;
	//music_main.openFromFile("Razrabotka\\MainMusic.wav");
	//music_main.play();

	Font font;
	font.loadFromFile("Razrabotka\\Font.ttf");

	Text textScore("", font, 15), textHealth("", font, 15), textMission("", font, 15);
	textScore.setColor(Color::Black);
	textMission.setColor(Color::Black);
	textHealth.setColor(Color::Black);
	Texture tex_map;
	tex_map.loadFromFile("Razrabotka\\Map.png");
	Sprite spr_map;
	spr_map.setTexture(tex_map);

	Time t1 =seconds(0.001f);
	Clock clock, gameTimeClock;
	int GameTime = 0;

	float CurrentFrame = 0;
	Image heroimage, enemyImage;
	enemyImage.loadFromFile("Razrabotka\\EnemyTileset.png");
	heroimage.loadFromFile("Razrabotka\\Tileset.png");
	Player p1(heroimage, 64, 64,35,0, 32, 32,"Player1");
	Enemy e1(enemyImage, 200, 200, 2, 64, 32, 32, "Enemy1");

	randomMapGenerate();
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		p1.update(&time);
		window.setView(view);
		window.clear();
		for (int i = 0; i < Height_Map; i++) 
		{
			for (int j = 0; j < Wight_Map; j++)
			{
				if (TileMap[i][j] == 'b')
					spr_map.setTextureRect(IntRect(437, 297, 32, 32));
				else if (TileMap[i][j] == 'l')
					spr_map.setTextureRect(IntRect(107, 33, 32, 32));
				else if (TileMap[i][j] == 'r')
					spr_map.setTextureRect(IntRect(140, 165, 32, 32));
				else if (TileMap[i][j] == 'd')
					spr_map.setTextureRect(IntRect(107, 231, 32, 32));
				spr_map.setPosition(j * 32, i * 32);
				window.draw(spr_map);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if (p1.life == true)
		{
			GameTime = gameTimeClock.getElapsedTime().asSeconds();
			p1.animationFunc(&CurrentFrame, &time);
			ostringstream playerScoreString, playerHealthString, gameTimeString;
			gameTimeString << GameTime;
			playerScoreString << p1.playerScore;
			playerHealthString << p1.health;
			textScore.setPosition(view.getCenter().x - 480, view.getCenter().y - 265);
			textHealth.setPosition(view.getCenter().x - 480, view.getCenter().y - 235);
			textScore.setString(" SCORE:" + playerScoreString.str() + "\n TIME:" + gameTimeString.str());
			textHealth.setString(" HEALTH:" + playerHealthString.str());
			window.draw(p1.sprite);
			window.draw(textScore);
			window.draw(textHealth);
		}
			if (p1.life == false)
			{
				view.setCenter(960, 540);
				textScore.setString("YOU LOSE");
				textScore.setScale(5, 5);
				textScore.setPosition(650, 480);
				window.draw(textScore);
				//music_main.stop();
			}
			window.display();
	}
		return 0;
}


