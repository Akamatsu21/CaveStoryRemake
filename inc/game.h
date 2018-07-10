#ifndef GAME_H
#define GAME_H

#include "graphics.h"
#include "player.h"
#include "level.h"
#include "hud.h"

// The class responsible for running the main game loop.

class Game
{
	Graphics graphics;	// game graphics
	HUD hud;			// user HUD
	Level level; 		// main level of the game
	Player player;		// player character
	
	void draw();
	void gameLoop();
	void update(float elapsed_time);

public:
	Game();
	~Game();
};

#endif