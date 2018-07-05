#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"
#include "hud.h"

class Graphics;

// The class responsible for running the main game loop.

class Game
{
	HUD hud;		// user HUD
	Level level; 	// main level of the game
	Player player;	// player character
	
	void draw(Graphics &graphics);
	void gameLoop();
	void update(float elapsed_time);

public:
	Game();
	~Game();
};

#endif