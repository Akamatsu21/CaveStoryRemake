#include "graphics.h"
#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite():
	Sprite(), current_frame(0), time_elapsed(0), visible(false), animation_once(false), current_animation(""), frame_time(0)
{
	
}

AnimatedSprite::AnimatedSprite(Graphics &graphics, std::string file_path, int src_x, int src_y, int h, int w, float start_x, float start_y, float time):
	Sprite(graphics, file_path, src_x, src_y, h, w, start_x, start_y), current_frame(0), time_elapsed(0), visible(true), animation_once(false), current_animation(""), frame_time(time)
{
	
}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int w, int h, Vector2 offset)
{
	std::vector<SDL_Rect> rects;
	for(int i = 0; i < frames; i++)
	{
		SDL_Rect r = { (x + i) * w, y * h, w, h };
		rects.push_back(r);
	}
	animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rects));
	offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::animationDone(std::string name)
{
	
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
	if(visible)
	{
		SDL_Rect dest = { x + offsets[current_animation].x, y + offsets[current_animation].y, src_rect.w * globals::SPRITE_SCALE, src_rect.h * globals::SPRITE_SCALE };
		
		SDL_Rect src = animations[current_animation][current_frame];
		
		graphics.blitSurface(spritesheet, &src, &dest);
	}
}

void AnimatedSprite::playAnimation(std::string name, bool once)
{
	animation_once = once;
	if(current_animation != name)
	{
		current_animation = name;
		current_frame = 0;
	}
}

void AnimatedSprite::resetAnimations()
{
	animations.clear();
	offsets.clear();
}

void AnimatedSprite::setupAnimations()
{
	addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	addAnimation(3, 0, 1, "RunRight", 16, 16, Vector2(0, 0));
}

void AnimatedSprite::setVisible(bool vis)
{
	visible = vis;
}

void AnimatedSprite::stopAnimation()
{
	current_frame = 0;
	animationDone(current_animation);
}

void AnimatedSprite::update(int elapsed_time)
{
	Sprite::update();
	
	time_elapsed += elapsed_time;
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