/*
 * tile_map.cpp
 *   g++ tile_logic.cpp rendering.cpp tile_map.cpp -o tile_test -lSDL2main -lSDL2 -lSDL2_image
 *
 */
 
#include "tile_map.h"
#include <algorithm>
#include <iostream>

sprite_set::sprite_set()
// empty constructor
// need to check for null sprite sheet before rendering
{
	sprite_size = 0;
	sprite_sheet = nullptr;
	sheet_width = 0;
	sheet_height = 0;
}

sprite_set::sprite_set(int set_size, int set_width, int set_height, text_ptr &set_sprites)
// constructs a sprite set
// all sprites are square (size is both the width and length of 1 sprite)
// width is the width of the sheet in sprites, not screen pixels
{
	sprite_size = set_size;
	sprite_sheet = std::move(set_sprites);
	sheet_width = set_width;
	sheet_height = set_height;
}

point sprite_set::get_screen_coords(int index) {
			int x = 0;
			int y = 0;
			
			int yCtr = index;
			for (int xCtr=index; xCtr%sheet_width != 0; xCtr--) {
				x = xCtr;
				yCtr -= 1;
			}
			
			y = yCtr/sheet_width;
			
			x = x*sprite_size;
			y = y*sprite_size;
						
			return point(x,y);
}

void tile_map_renderer::set_current_sprite(int ind) {
	point coords = sprites.get_screen_coords(ind);
			
	current_sprite.x = coords.x();
	current_sprite.y = coords.y();
}


void tile_map_renderer::set_screen_dest(int x, int y, int cam_x, int cam_y) {
	screen_dest.x = (x*(sprites.sprite_size)) - cam_x;
	screen_dest.y = (y*(sprites.sprite_size)) - cam_y;			
}
	
	
tile_map_renderer::tile_map_renderer(sprite_set &set_sprites, dyn_map &set_map) {
	sprites.sprite_size = set_sprites.sprite_size;
	sprites.sprite_sheet = std::move(set_sprites.sprite_sheet);
	sprites.sheet_width = set_sprites.sheet_width;
	sprites.sheet_height = set_sprites.sheet_height;
						
	reset_map(set_map);
			
	current_sprite.w = sprites.sprite_size;
	current_sprite.h = sprites.sprite_size;
			
	screen_dest.w = sprites.sprite_size;
	screen_dest.h = sprites.sprite_size;
}
		
void tile_map_renderer::reset_map(dyn_map &rset_map) {
	tile_map = rset_map;
}

void tile_map_renderer::render_tiles(rend_ptr &renderer, camera &cam) {
	point cam_loc = cam.get_screen_loc();
	if (sprites.sprite_sheet == nullptr) {
		std::cout<<"Warning! tried to render a sprite map with no set texture (tile_map_renderer)"<<std::endl;
	} else {
		for (int y = 0; dyn_row &current_row : tile_map) {
			for (int x = 0; int &current_tile : current_row) {
				set_current_sprite(current_tile);
				set_screen_dest(x, y, cam_loc.x(), cam_loc.y());
				render_texture(sprites.sprite_sheet, renderer, current_sprite, screen_dest);
				++x;
			}
			++y;
		}
	}
}
