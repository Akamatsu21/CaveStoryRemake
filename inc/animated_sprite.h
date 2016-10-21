#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <vector>
#include "globals.h"
#include "sprite.h"

//The class holding information for animated sprites

class AnimatedSprite: public Sprite
{
	unsigned int current_frame;
	double time_elapsed;
	bool visible;
	
	std::map<std::string, std::vector<SDL_Rect> > animations;
	std::map<std::string, Vector2> offsets;
	
protected:
	bool animation_once;
	std::string current_animation;
	double frame_time;
	
	void addAnimation(int frames, int x, int y, std::string name, int w, int h, Vector2 offset); //add a new animation to the map
	virtual void animationDone(std::string name); //happens when animation ends
	void resetAnimations(); //clear all animations from the map
	void setVisible(bool vis); //change visibility
	void stopAnimation(); //stop playing the current animation
	
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y, float time);
	
	void draw(Graphics &graphics, int x, int y); //draw the sprite to the screen
	void playAnimation(std::string name, bool once = false); //plays the animation if it's not played already
	virtual void setupAnimations(); //sets up all of the sprite's animations
	virtual void update(int elapsed_time); //update to the next frame of the animation
};

#endif