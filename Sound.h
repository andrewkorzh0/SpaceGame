#pragma once
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

class SoundManager
{
	SoundBuffer pewpew_m;
	SoundBuffer hit_m;
	SoundBuffer super_pewpew_m;
public:
	Sound pewpew;
	Music soundtrack;
	Sound hit;
	Sound super_pewpew;
	SoundManager()
	{
		pewpew_m.loadFromFile("Assets/Sounds/pewpew.wav");
		hit_m.loadFromFile("Assets/Sounds/hit.wav");
		super_pewpew_m.loadFromFile("Assets/Sounds/super_pewpewpew.wav");
		soundtrack.openFromFile("Assets/Sounds/soundtrack.wav");

		pewpew.setBuffer(pewpew_m);
		super_pewpew.setBuffer(super_pewpew_m);
		hit.setBuffer(hit_m);

		soundtrack.setLoop(true);

		soundtrack.setVolume(50);
		hit.setVolume(50);
		super_pewpew.setVolume(100);
		pewpew.setVolume(50);
	}
};