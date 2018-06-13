#include "graphics.h"
#include "animated_sprite.h"

// Default constructor.
AnimatedSprite::AnimatedSprite():
	Sprite(), current_frame(0), time_elapsed(0), visible(false), animation_once(false), current_animation(""), frame_time(0)
{}

// Constructor.
AnimatedSprite::AnimatedSprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y, float time):
	Sprite(graphics, file_path, src_x, src_y, h, w, start_x, start_y), current_frame(0), time_elapsed(0), visible(true), animation_once(false), current_animation(""), frame_time(time)
{}

// Add a new animation to the animations map.
void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int w, int h, Vector2 offset)
{
	// Construct a set of frames for the animation.
	std::vector<SDL_Rect> rects;
	for(int i = 0; i < frames; ++i)
	{
		SDL_Rect r = { (x + i) * w, y * h, w, h };
		rects.push_back(r);
	}

	// Add it to the animations and offsets.
	animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rects));
	offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

// Draw sprite onto the screen if it's visible.
void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
	if(visible)
	{
		SDL_Rect dest = { x + offsets[current_animation].x, y + offsets[current_animation].y, src_rect.w * globals::SPRITE_SCALE, src_rect.h * globals::SPRITE_SCALE };
		
		SDL_Rect src = animations[current_animation][current_frame];
		
		graphics.blitSurface(spritesheet, &src, &dest);
	}
}

// Set name as the currently playing animation (if not played already).
void AnimatedSprite::playAnimation(std::string name, bool once)
{
	animation_once = once;
	if(current_animation != name)
	{
		current_animation = name;
		current_frame = 0;
	}
}

// Delete all saved animations.
void AnimatedSprite::resetAnimations()
{
	animations.clear();
	offsets.clear();
}

// Setter for visible.
void AnimatedSprite::setVisible(bool vis)
{
	visible = vis;
}

// Stop playing the current animation.
void AnimatedSprite::stopAnimation()
{
	current_frame = 0;
	animationDone(current_animation);
}

// Update to the next frame of the animation.
void AnimatedSprite::update(int elapsed_time)
{
	Sprite::update();
	
	time_elapsed += elapsed_time;
	
	// If more time has passed in the last frame than specified frame time, show the next frame.
	if(time_elapsed > frame_time)
	{
		time_elapsed -= frame_time;
		if(current_frame < animations[current_animation].size() - 1)
		{
			current_frame++;
		}
		else
		{
			if(animation_once) setVisible(false);
			stopAnimation();
		}
	}
}