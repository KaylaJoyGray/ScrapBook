#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "tile_logic.h"
#include "rendering.h"
#include "camera.h"

struct sprite_set {
	text_ptr sprite_sheet;
	int sprite_size;
	int sheet_width;
	int sheet_height;
	sprite_set();
	sprite_set(int set_size, int set_width, int set_height, text_ptr &set_sprites);
	point get_screen_coords(int index);
};

class tile_map_renderer {
	private:
		sprite_set sprites;
		
		dyn_map tile_map;
				
		SDL_Rect current_sprite;
		SDL_Rect screen_dest;
		
		void set_current_sprite(int ind);
		void set_screen_dest(int x, int y, int cam_x, int cam_y);
	public:
		tile_map_renderer(sprite_set &set_sprites, dyn_map &set_map);
		void reset_map(dyn_map &rset_map);
		void render_tiles(rend_ptr &renderer, camera &cam);
};

#endif
