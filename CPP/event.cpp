/*
 * event.cpp
 * 
 */

#include "event.h"

std::vector<SDL_Event> get_events() {
	std::vector<SDL_Event> ret_events;
	
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		ret_events.push_back(event);
	}
	
	return ret_events;
}
