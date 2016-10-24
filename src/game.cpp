#include <iostream>
#include <SDL2\SDL.h>
#include "graphics.h"
#include "input.h"
#include "game.h"

namespace
{
	const int FPS = 50;
	const int MAX_FRAME_TIME = 100;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

void Game::draw(Graphics &graphics)
{
	graphics.clear();
	
	level.draw(graphics);
	player.draw(graphics);
	
	graphics.flip();
}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	SDL_Event event;
	int last_update_time = SDL_GetTicks();
	
	level = Level(graphics, "map 1", Vector2(100, 100));
	player = Player(graphics, 100, 100);
	
	for(;;)
	{
		input.beginNewFrame();

		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
			{
				if(!event.key.repeat)
				{
					input.keyDownEvent(event);
				}
			}
			else if(event.type == SDL_KEYUP)
			{
				input.keyUpEvent(event);
			}
			else if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
			{
				
			}
			else if(event.type == SDL_QUIT)
			{
				return;
			}
		}
		
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
		
		int current_time = SDL_GetTicks();
		int elapsed_time = current_time - last_update_time;
		update(std::min(MAX_FRAME_TIME, elapsed_time));
		last_update_time = current_time;
		
		draw(graphics);
	}
}

void Game::update(float elapsed_time)
{
	level.update(elapsed_time);
	player.update(elapsed_time);
}

Game::~Game()
{
	
}