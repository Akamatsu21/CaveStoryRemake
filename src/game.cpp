#include <iostream>
#include <SDL2\SDL.h>
#include "graphics.h"
#include "input.h"
#include "game.h"

namespace
{
	const int FPS = 50;				// maximum frames per second
	const int MAX_FRAME_TIME = 100;	// maximum frame length
}

// Constructor - starts the game.
Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

// Refresh game graphics.
void Game::draw(Graphics &graphics)
{
	graphics.clear();
	
	level.draw(graphics);
	player.draw(graphics);
	hud.draw(graphics);	// HUD always has to be drawn last!
	
	graphics.flip();
}

// Core game progression logic.
void Game::gameLoop()
{
	Graphics graphics;						// game graphics
	Input input;							// game input
	int last_update_time = SDL_GetTicks();	// get starting time
	
	level = Level(graphics, "map1"); 						// create the level
	player = Player(graphics, level.getPlayerSpawnPoint());	// create the player
	hud = HUD(graphics, player);							// create the HUD
	
	for(;;)
	{
		// Reset the pressed keys in the input.
		input.beginNewFrame();

		// Listen for an event.
		SDL_Event event;
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				if(!event.key.repeat)
				{
					// Record a key pressed.
					input.keyDownEvent(event);
				}
			}
			else if(event.type == SDL_KEYUP)
			{
				// Record a key released.
				input.keyUpEvent(event);
			}
			else if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				
			}
			else if(event.type == SDL_QUIT)
			{
				// Window closed.
				return;
			}
		}
		
		/* Handle specific inputs. */

		// Looking up and down.
		if(input.wasPressed(SDL_SCANCODE_UP))
		{
			player.lookUp();
		}
		else if(input.wasPressed(SDL_SCANCODE_DOWN))
		{
			player.lookDown();
		}

		if(input.wasReleased(SDL_SCANCODE_UP))
		{
			player.stopLookingUp();
		}
		
		if(input.wasReleased(SDL_SCANCODE_DOWN))
		{
			player.stopLookingDown();
		}

		// Moving.
		if(input.wasPressed(SDL_SCANCODE_ESCAPE))
		{
			return;
		}
		else if(input.isHeld(SDL_SCANCODE_LEFT))
		{
			player.moveLeft();
		}
		else if(input.isHeld(SDL_SCANCODE_RIGHT))
		{
			player.moveRight();
		}
		else
		{
			player.stopMoving();
		}

		// Jumping.
		if(input.wasPressed(SDL_SCANCODE_Z))
		{
			player.jump();
			player.reduceHP();
		}
		
		// Calculate elapsed time and update the objects.
		int current_time = SDL_GetTicks();
		int elapsed_time = current_time - last_update_time;
		update(std::min(MAX_FRAME_TIME, elapsed_time));

		// Set a new update time.
		last_update_time = current_time;
		
		// Update the screen.
		draw(graphics);
	}
}

// Update in-game objects,
void Game::update(float elapsed_time)
{
	level.update(elapsed_time);
	player.update(elapsed_time);
	hud.update(elapsed_time);

	// Check player collisions with other tiles.	
	std::vector<Rectangle> rects = level.checkTileCollisions(player.getBoundingBox());
	if(rects.size() > 0)
	{
		player.handleTileCollisions(rects);
	}

	// Check player collisions with slopes.
	std::vector<Slope> slopes = level.checkSlopeCollisions(player.getBoundingBox());
	if(slopes.size() > 0)
	{
		player.handleSlopeCollisions(slopes);
	}
}

// Destructor.
Game::~Game()
{
	
}