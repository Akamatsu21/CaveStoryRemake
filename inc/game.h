#ifndef GAME_H
#define GAME_H

#include "animated_sprite.h"

class Graphics;

//The class responsible for running the main game loop.

class Game
{
	AnimatedSprite player;
	
	void draw(Graphics &graphics);
	void gameLoop();
	void update(float elapsed_time);

public:
	Game();
	~Game();
};

#endif