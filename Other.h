#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int bullet_array_counter = 0;
bool can_fire = true;

class Bullet
{
public:
	Sprite sprite;
	Texture texture;
	bool isActive = false;
	double x = -100, y = -100;
	double speed = 10;

	Bullet()
	{
		texture.loadFromFile("Assets/Sprites/bullet_01.png");
		sprite.setScale(4, 4);
		sprite.setTexture(texture);
		x = -100, y = -100;
	}

	void Restart(double X, double Y)
	{
		x = X;
		y = Y;
		speed = 10;
		isActive = true;
	}

	void Update()
	{
		if(isActive)
		{
			y -= speed;
			sprite.setPosition(x, y);
			if (y <= -100)
			{
				isActive = false;
				speed = 0;
			}
		}
	}

};

class SuperBullet
{
public:

	Sprite sprite;
	Texture texture;
	bool isActive = false;
	double x = 300, y = 100;
	double speed = 5;
	double width, height;

	SuperBullet()
	{
		texture.loadFromFile("Assets/Sprites/bullet_01.png");
		sprite.setScale(60, 60);
		sprite.setTexture(texture);
		height = sprite.getLocalBounds().height * sprite.getScale().y;
		width = sprite.getLocalBounds().width * sprite.getScale().x;
	}

	void Restart(double X, double Y)
	{
		x = X;
		y = Y;
		speed = 5;
		isActive = true;
	}

	void Update()
	{
		if (isActive)
		{
			y -= speed;
			sprite.setPosition(x, y);
			if (y <= -(sprite.getLocalBounds().height* sprite.getScale().y))
			{
				isActive = false;
				speed = 0;
			}
		}
	}

};


class Heart
{
public:
	Texture texture;
	Sprite sprite;
	bool isActive = true;
	Heart()
	{
		texture.loadFromFile("Assets/Sprites/heart.png");
		sprite.setScale(4,4);
		sprite.setTexture(texture);
	}
	void setPosition(double X, double Y)
	{
		sprite.setPosition(X, Y);
	}
};

class Star
{
public:
	Texture texture;
	Sprite sprite;
	double x = 0, y = 0;
	double speed = 0; // from 1 to 10

	Star()
	{
		int id = rand() % 2 + 1;
		texture.loadFromFile("Assets/Sprites/star_0" + to_string(id) + ".png");
		sprite.setTexture(texture);
		speed = rand() % 10 + 1;
		x = rand() % (window_size_x + 10);
		y = rand() % (window_size_y + 10);
		int scale = rand() % 3 + 1;
		sprite.setScale(scale, scale);
	}

	void Update()
	{
		y += speed;
		if (y >= window_size_y + 50)
		{
			int id = rand() % 2 + 1;
			texture.loadFromFile("Assets/Sprites/star_0" + to_string(id) + ".png");
			sprite.setTexture(texture);
			speed = rand() % 10 + 1;
			x = rand() % (window_size_x + 10);
			y = -10;
			int scale = rand() % 4 + 1;
			sprite.setScale(scale, scale);
		}
		sprite.setPosition(x, y);

	}
};