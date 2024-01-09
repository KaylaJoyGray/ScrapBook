#ifndef SPRITES_H
#define SPRITES_H

#include "rendering.hpp"
#include <string>
#include <vector>
#include <utility>

namespace sprites {

	enum Sprite_Set_ID {
		sprites_none,
		sprites_cursor,
		sprites_font1,
		sprites_universe,
		sprites_sector,
		sprites_shade,
		sprites_ship,
		sprites_mod1,	//extra sprite sections for modding, when mod system is fleshed out
		sprites_mod2,
		sprites_mod3
	};

	struct Sprite_Set {
		Sprite_Set_ID id = sprites_none;
		text_ptr sprite_sheet;
		int sprite_size;	//size in pixels, square
		int sheet_width;	//width and height in # of sprites, not screen pixels
		int sheet_height;
		Sprite_Set();
		Sprite_Set(Sprite_Set_ID set_id, int set_size, int set_width, int set_height, text_ptr &set_sprites);
		point get_screen_coords(unsigned int index);
	};

	struct Offset {
		double x, y, z;	//0.0 to 39.0 on each axis
	};

	class Sprite_Manager {
		private:
			std::vector<Sprite_Set> loaded_sprites;

			SDL_Rect current_sprite;
			SDL_Rect screen_dest;

			void set_screen_dest(int x, int y);
		public:
			Sprite_Manager();
			void add_Sprite_Set(Sprite_Set &s);

			void display_map(Sprite_Set_ID sheet, point loc, rend_ptr rend,
							 std::vector<std::vector<int>> ind_map,
							 std::vector<std::vector<int>> rot_map = {{0}});

			void display_map(point loc, rend_ptr rend,
							 std::vector<std::pair<Sprite_Set_ID, std::vector<std::vector<int>>>> ind_map,
							 std::vector<std::vector<std::vector<int>>> rot_map);
			void display_map(point loc, rend_ptr rend,
							 std::vector<std::pair<Sprite_Set_ID, std::vector<std::vector<int>>>> ind_map,
							 std::vector<std::vector<std::vector<int>>> rot_map,
							 std::vector<std::vector<std::vector<Offset>>> off_map);
	};

	struct render_data {
		Sprite_Set_ID sheet;
		point loc;
		std::vector<std::vector<int>> ind_map = {{0}};
		std::vector<std::vector<int>> rot_map = {{0}};
	};

}

#endif
