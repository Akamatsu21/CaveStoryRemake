#ifndef GAME_H
#define GAME_H

//The class responsible for running the main game loop.

class Graphics;

class Game
{
	void draw(Graphics &graphics);
	void gameLoop();
	void update(float elapsed_time);

public:
	Game();
	~Game();
};

#endif