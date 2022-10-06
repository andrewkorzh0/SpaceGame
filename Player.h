#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

//Global Values
int window_size_x = 1280, window_size_y = 720;
int frame_counter = 0;
bool inGame = false;

class Player
{
public:
    Sprite sprite;
    Texture texture_01;
    Texture texture_02;
    double width;
    double height;
    double x;
    double y;
    int health = 5;
    int score = 0;
    double speed = 5;
    double super_blast_charge = 100;

    Player(double X, double Y) : x(X), y(Y)
    {
        texture_01.loadFromFile("Assets/Sprites/player/player_01.png");
        texture_02.loadFromFile("Assets/Sprites/player/player_02.png");
        sprite.setScale(4, 4);
        width = texture_01.getSize().x * sprite.getScale().x;
        height = texture_01.getSize().y * sprite.getScale().y;
    }

    void Update()
    {

        if (super_blast_charge >= 100)
            super_blast_charge = 100;
        else super_blast_charge += 0.15;

        if ((Keyboard::isKeyPressed(Keyboard::Left)) && x >= 0)
        {
            x -= speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) && x <= window_size_x - width)
        {
            x += speed;
        }

        //Updates

        if ((frame_counter / 10) % 2 == 0)
            sprite.setTexture(texture_01);
        else sprite.setTexture(texture_02);
        sprite.setPosition(x, y);
    }

};
