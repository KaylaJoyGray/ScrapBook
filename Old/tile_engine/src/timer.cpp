/*
 * timer.cpp
 *
 * Copyright 2023 Kayla Gray
 *
 */

#include "timer.hpp"
#include "SDL2/SDL.h"

delta_timer::delta_timer()
// set the inital time
{
	this->last_time = SDL_GetTicks64();
}

double delta_timer::get_delta()
// get the delta time, in seconds
{
	uint64 current = SDL_GetTicks64();
	double delta_t = (current - this->last_time) / 1000.0;

	this->last_time = current;

	return (delta_t);
}
