/*
 * timing.cpp
 * 
 */

#include "timing.hpp"
#include <SDL2/SDL.h>

timer::timer(int set_FPS) {
	this->new_FPS(set_FPS);
}

void timer::start_frame()
// called at start of frame to record time
{
	this->frame_start = SDL_GetTicks();
}

void timer::delay_frame()
// called at end of frame to enforce timing
{
	frame_time = SDL_GetTicks() - frame_start;
				
	if (frame_delay > frame_time) {
		SDL_Delay(frame_delay - frame_time);
	}
}

void timer::new_FPS(int set_FPS)
// sets the FPS to a new value
{
	this->FPS = set_FPS;
	this->frame_delay = 1000/FPS;
}
