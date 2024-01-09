/*
 * main.cpp
 * 
 */

#include "tile_logic.h"
#include "tile_map.h"
#include "event.h"
#include "camera.h"
#include "rendering.h"
#include <stdlib.h>
#include <iostream>

point get_current_display_mode() {
	point screen_dims = point(0,0);
	SDL_DisplayMode current_display;
	
	for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {
		if (SDL_GetCurrentDisplayMode(i, &current_display) != 0) {
			std::cerr<<"SDL Error! "<<SDL_GetError()<<std::endl;
		} else {
			screen_dims = point(current_display.w, current_display.h);
		}
	}
	
	return screen_dims;
}

int main (int argc, char **argv) {	
	int width = 1920;
	int height = 1080;
		
	if (init_graphics() == 0) 
	{
		wind_ptr window(create_window("Test", width, height));
	
		if (window != nullptr) {			
			rend_ptr test_rend(create_renderer(window, -1, SDL_RENDERER_ACCELERATED));
			
			point screen_dims = get_current_display_mode();
			
			camera game_cam = camera(0, 0, 0, 0, screen_dims.x(), screen_dims.y());
			
			//SDL_RenderSetScale(test_rend.get(), 2, 2);
			
			set_render_draw_color(test_rend, 0, 0, 0, 100);
			
			text_ptr sp = load_texture("test_spritesheet.png", test_rend);
			sprite_set t = sprite_set(32, 2, 1, sp);
		
			dyn_map test_map;
			populate_tiles(50,50,test_map);
			point d = point(21,21);
			
			dyn_map test_camera_map;
			populate_tiles(50,50,test_camera_map);
			
			draw_area(1,d,d,test_map);
				
			tile_map_renderer test_renderer = tile_map_renderer(t,test_map);
			
			std::vector<SDL_Event> frame_events;
			
			int running = 100000;
			while (running) {
				frame_events = get_events();
				game_cam.process_events(frame_events, t.sprite_size);
				
				clear_render(test_rend);
	
				test_renderer.render_tiles(test_rend, game_cam);
						
				present_render(test_rend);
				
				running -= 1;
			}
		}
	}

	multimedia_quit();
	
	return 0;
}
