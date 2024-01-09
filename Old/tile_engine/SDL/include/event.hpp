#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>
#include <vector>

namespace global_event {
	
	std::vector<SDL_Event> get_events();

}
#endif
