/*
 * camera.cpp
 * 
 */

#include "camera.h"

camera::camera(int init_scrx, int init_scry, int init_tx, int init_ty, int w, int h) {
	screen_loc = point(init_scrx, init_scry);
	tile_loc = point(init_tx, init_ty);
	width = w;
	height = h;
	vel_x = 0;
	vel_y = 0;
}

point camera::get_screen_loc() {
	return screen_loc;
}

point camera::get_tile_loc() {
	return tile_loc;
}

point camera::get_tile_coords(int screen_x, int screen_y, int tile_size_px)
// get tile coordinates from screen coordinates.
// used to find where in the map the camera is, for example.
{
	int tile_x = 0;
	int tile_y = 0;
	
	tile_x = screen_x / tile_size_px;
	tile_y = screen_y / tile_size_px;
	
	return point(tile_x, tile_y);
}

void camera::update_loc(int tile_size_px) {
	int new_x = screen_loc.x()+vel_x;
	int new_y = screen_loc.y()+vel_y;
	
	screen_loc = point(new_x, new_y);
	
	point new_tile_coords = get_tile_coords(new_x, new_y, tile_size_px);
	if (out_of_bounds(new_tile_coords, )
}

void camera::process_events(std::vector<SDL_Event> &frame_events, int tile_size_px) {
	for (SDL_Event &event : frame_events) {
		if (event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_w:
					vel_y = -1;
					break;
				case SDLK_s:
					vel_y = 1;
					break;
				case SDLK_a:
					vel_x = -1;
					break;
				case SDLK_d:
					vel_x = 1;
					break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
				case SDLK_w:
					vel_y = 0;
					break;
				case SDLK_s:
					vel_y = 0;
					break;
				case SDLK_a:
					vel_x = 0;
					break;
				case SDLK_d:
					vel_x = 0;
					break;
			}
		}
	}
	update_loc(tile_size_px);
}

