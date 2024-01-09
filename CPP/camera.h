#ifndef CAMERA_H
#define CAMERA_H

#include "tile_logic.h"
#include <SDL2/SDL.h>
#include <vector>

class camera {
	private:
		point screen_loc = point(0,0);
		point tile_loc = point(0,0);
		int width;
		int height;
		int vel_x;
		int vel_y;
	public:
		camera(int init_scrx, int init_scry, int init_tx, int init_ty, int w, int h);
		point get_screen_loc();
		point get_tile_loc();
		point get_tile_coords(int screen_x, int screen_y, int tile_size_px);
		void update_loc(int tile_size_px);
		void process_events(std::vector<SDL_Event> &frame_events, int tile_size_px);
};

#endif
