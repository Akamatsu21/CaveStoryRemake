#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <map>
#include <vector>
#include "globals.h"
#include "sprite.h"

// The class holding information for animated sprites.

class AnimatedSprite: public Sprite
{
	unsigned int current_frame;	// what frame the animation is currently at
	double time_elapsed;		// time since the last frame
	bool visible;				// is the sprite visible
	
	std::map<std::string, std::vector<SDL_Rect>> animations;	// set of frames for each animation
	std::map<std::string, Vector2> offsets;						// set of offsets for each animation
	
protected:
	bool animation_once;			// true if animation isn't repeated
	std::string current_animation;	// current animmation playing
	double frame_time;				// duration of a single frame
	
	void addAnimation(int frames, int x, int y, std::string name, int w, int h, Vector2 offset);
	void resetAnimations();
	void setVisible(bool vis);
	void stopAnimation();
	
	virtual void animationDone(std::string name) = 0; // happens when animation ends
	virtual void setupAnimations() = 0; // sets up all of the sprite's animations
	
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y, float time);
	
	void draw(Graphics &graphics, int x, int y);
	void playAnimation(std::string name, bool once = false);
	virtual void update(int elapsed_time);
};

#endif