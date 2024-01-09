/*
 * sprites.cpp
 *
 * Sprites!
 * Copyright 2023 Kayla Gray
 *
 */

#include "sprites.hpp"
#include "global_settings.hpp"
#include "global_error.hpp"
#include <iostream>

using namespace sprites;

namespace sprites {
// sprites START BRACE

static double resolve_rot(int sig)
// resolves rotation settings into degrees
// 1 = 90  degree rotation
// 2 = 180 degree rotation
// 3 = 270 degree rotation
{
	switch (sig) {
		case 1:
			return 90.0;
		case 2:
			return 180.0;
		case 3:
			return 270.0;
		default:
			global_error::log_error("sprites: resolve_rot: invalid rotation requested");
			return 0.0;
	}
}

point Sprite_Set::get_screen_coords(unsigned int index)
// given the index of a sprite, returns the pixel coordinates
{
	int x = 0;
	int y = 0;

	for (int Ctr = 0; Ctr < index; Ctr++ ) {
		x++;

		if (((Ctr+1)%sheet_width) == 0)
		// reached new line, reset x and increase y
		{
			x = 0;
			y++;
		}
	}

	x = x*sprite_size;
	y = y*sprite_size;

	return point(x,y);
}

Sprite_Set::Sprite_Set()
// empty constructor
// need to check for null sprite sheet before rendering
{
	id = sprites_none;
	sprite_size = 0;
	sprite_sheet = nullptr;
	sheet_width = 0;
	sheet_height = 0;
}

Sprite_Set::Sprite_Set(Sprite_Set_ID set_id, int set_size, int set_width, int set_height, text_ptr &set_sprites)
// constructs a sprite set
// all sprites are square (size is both the width and length of 1 sprite)
// width is the width of the sheet in sprites, not screen pixels
{
	id = set_id;
	sprite_size = set_size;
	sprite_sheet = std::move(set_sprites);
	sheet_width = set_width;
	sheet_height = set_height;
}

Sprite_Manager::Sprite_Manager()
// constructor
{
	this->current_sprite.w = global_settings::SPRITE_SIZE;
	this->current_sprite.h = global_settings::SPRITE_SIZE;

	this->screen_dest.w = global_settings::SPRITE_SIZE*global_settings::SPRITE_SCALE;
	this->screen_dest.h = global_settings::SPRITE_SIZE*global_settings::SPRITE_SCALE;
}

void Sprite_Manager::add_Sprite_Set(Sprite_Set &s)
// add a sprite sheet to the list of loaded sprite sheets
{
	loaded_sprites.push_back(s);
}

void Sprite_Manager::set_screen_dest(int x, int y) {
	screen_dest.x = x;
	screen_dest.y = y;
}

void Sprite_Manager::display_map(Sprite_Set_ID sheet, point loc, rend_ptr rend,
								 std::vector<std::vector<int>> ind_map,
								 std::vector<std::vector<int>> rot_map)
// renders a sprite map to the screen, the "map" to render must be provided as a 2d vector of integers
// corresponding to the sprite index
{
	Sprite_Set current_set;

	//locate the correct sprite sheet to render
	for (Sprite_Set s : this->loaded_sprites) {
		if (s.id == sheet) {
			current_set = s;
			break;
		}
	}

	//no matching Sprite_Set_ID found: this means the requested sprite sheet was not loaded by the Sprite_Manager
	if (current_set.id == sprites_none) {
		global_error::fatal_error("Error! Sprite sheet not found");
	}

	this->set_screen_dest(loc.x(), loc.y());
	int current_x = loc.x();
	int current_y = loc.y();

	//counters for sprite rotation
	int rx = 0;
	int ry = 0;

	for (auto row : ind_map) {
		for (auto current_index : row) {
			point coords = current_set.get_screen_coords(current_index);

			this->current_sprite.x = coords.x();
			this->current_sprite.y = coords.y();

			if (rot_map[0][0] == 0) {		// prevent overflow of rot_map, not foolproof
				render_texture(current_set.sprite_sheet,
							   rend,
							   this->current_sprite,
							   this->screen_dest);
			} else {
				render_texture(current_set.sprite_sheet,
							   rend,
							   this->current_sprite,
							   this->screen_dest,
							   resolve_rot(rot_map[ry][rx]));
			}

			current_x += screen_dest.w;
			this->set_screen_dest(current_x, current_y);
			rx++;
		}
		current_x = loc.x();
		current_y += screen_dest.h;
		ry++;

		this->set_screen_dest(current_x, current_y);
	}
}

void Sprite_Manager::display_map(point loc, rend_ptr rend,
								 std::vector<std::pair<Sprite_Set_ID, std::vector<std::vector<int>>>> ind_map,
								 std::vector<std::vector<std::vector<int>>> rot_map)
// this version can render multiple "maps"
// the maps will be rendered in the order that is reflected in the array
// ex. ind_map[0] is displayed first
{
	auto s_ind = ind_map.size();
	auto s_rot = rot_map.size();

	if (s_ind != s_rot) {
			global_error::log_error("sprites: display_map[]: number of indices does not match rotations\n"
									"cannot render");
			return;
	}

	int cnt = 0;
	for (auto m : ind_map) {
		if (rot_map[cnt][0][0] != 0) {
			this->display_map(ind_map[cnt].first, loc, rend, ind_map[cnt].second, rot_map[cnt]);
		} else {
			this->display_map(ind_map[cnt].first, loc, rend, ind_map[cnt].second);
		}
		//std::cout<<"layer "<<cnt<<std::endl;
		cnt++;
	}
}

// sprites END_BRACE
}

