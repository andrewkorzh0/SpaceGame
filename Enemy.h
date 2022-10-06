#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int spawn_counter = 0;
int spawn_rate = 90;
int enemies_array_counter = 0;
double enemy_width = 112;
double enemy_height = 104;
int enemies_size = 10;

class Enemy
{
public:

    Texture enemy_texture_01;
    Texture enemy_texture_02;
    Sprite sprite;
    double x;
    double y;
    double speed = 2; //vertical speed -y
    bool isActive = false;
    int spawn_frame = 0;

    void Restart(double X)
    {
        enemy_texture_01.loadFromFile("Assets/Sprites/enemy_01.png");
        enemy_texture_02.loadFromFile("Assets/Sprites/enemy_02.png");
        y = 0 - enemy_height;
        x = X;
        spawn_frame = frame_counter;
        sprite.setScale(4, 4);
        isActive = true;
    }

    void Update()
    {
        if (y >= window_size_y + enemy_height / 2)
            isActive = false;
        y += speed;
        if (((frame_counter + spawn_frame) / 10) % 2 == 0)
            sprite.setTexture(enemy_texture_01);
        else sprite.setTexture(enemy_texture_02);
        sprite.setPosition(x, y);
    }
};
