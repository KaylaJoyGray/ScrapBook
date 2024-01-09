/*
 * global_settings.cpp
 * 
 */

#include "global_settings.hpp"

void global_settings::LOAD_SETTINGS()
//loads settings
{
	global_settings::SCREEN_WIDTH = 1280;
	global_settings::SCREEN_HEIGHT = 720;
	global_settings::FPS = 35;
	global_settings::FONT_SIZE = 16;
	global_settings::FONT_SCALE = 1;
	global_settings::SPRITE_SIZE = 16;
	global_settings::SPRITE_SCALE = 1;

	global_settings::SAVE_PATH = "./saves/";
	
	return;
}
