#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"

class Graphics;

//The class responsible for running the main game loop.

class Game
{
	Level level;
	Player player;
	
	void draw(Graphics &graphics);
	void gameLoop();
	void update(float elapsed_time);

public:
	Game();
	~Game();
};

#endif