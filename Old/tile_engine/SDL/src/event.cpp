/*
 * event.cpp
 * 
 */

#include "event.hpp"

std::vector<SDL_Event> global_event::get_events() {
	std::vector<SDL_Event> ret_events;
	
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		ret_events.push_back(event);
	}
	
	return ret_events;
}
