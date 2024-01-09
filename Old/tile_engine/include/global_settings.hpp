#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <string>

namespace global_settings {
	inline int SCREEN_WIDTH;
	inline int SCREEN_HEIGHT;
	inline int FPS;
	inline int FONT_SIZE;
	inline int FONT_SCALE;
	inline int SPRITE_SIZE;
	inline int SPRITE_SCALE;
	inline std::string SAVE_PATH;
		
	void LOAD_SETTINGS();
}

#endif
