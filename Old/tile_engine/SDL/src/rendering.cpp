/*
 * rendering.cpp
 *
 */

#include "rendering.hpp"
#include <iostream>
#include <stdlib.h>

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

// custom deleters for the SDL wrapper
void SDLw_delet::operator() (SDL_Window *wind) {
	SDL_DestroyWindow(wind);
}

void SDLw_delet::operator() (SDL_Renderer *rend) {
	SDL_DestroyRenderer(rend);
}

void SDLw_delet::operator() (SDL_Texture *text) {
	SDL_DestroyTexture(text);
}

void SDLw_delet::operator() (SDL_Surface *surf) {
	SDL_FreeSurface(surf);
}

void SDLw_delet::operator() (SDL_Event *event) {

}

wind_ptr create_window(const char* title, int width, int height)
// returns a unique pointer for SDL_CreateWindow
{
	return wind_ptr(
	SDL_CreateWindow(
					title,
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					width,
					height,
					0	//SDL_WINDOW_FULLSCREEN_DESKTOP
	),SDLw_delet());
}

rend_ptr create_renderer(wind_ptr &wind, int index, int flags)
// returns a unique pointer for SDL_CreateRenderer
{
	return rend_ptr(
	SDL_CreateRenderer(
					wind.get(),
					index,
					flags
	),SDLw_delet());
}

void set_render_draw_color(rend_ptr &renderer, int r, int g, int b, int a)
// sets the draw color of an SDL renderer
{
	SDL_SetRenderDrawColor(renderer.get(), r, g, b, a);
	SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_MOD);
}

void clear_render(rend_ptr &renderer)
// clears the renderer with the draw color
{
	SDL_RenderClear(renderer.get());
}

void present_render(rend_ptr &renderer)
// presents the rendering
{
	SDL_RenderPresent(renderer.get());
}

int render_texture(text_ptr &texture, rend_ptr &renderer)
// renders a texture
{
	return SDL_RenderCopy(renderer.get(), texture.get(), NULL, NULL);
}

int render_texture(text_ptr &texture, rend_ptr &renderer, SDL_Rect &src, SDL_Rect &dest, double rot)
// renders a texture with src and dest rectangles
{
	return SDL_RenderCopyEx(renderer.get(), texture.get(), &src, &dest, rot, NULL, SDL_FLIP_NONE);
}

text_ptr load_texture(const char *file_path, rend_ptr &renderer)
// returns a unique pointer to a texture loaded from image file
{
	text_ptr result;

	surf_ptr loaded_surface(IMG_Load(file_path), SDLw_delet());

	if (loaded_surface == nullptr) {
		std::cerr<<"SDL image error! "<<IMG_GetError()<<std::endl;
	} else {
		result = text_ptr(SDL_CreateTextureFromSurface(renderer.get(), loaded_surface.get()), SDLw_delet());
	}

	return result;
}

void init_graphics()
// initialize SDL Video
{
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		std::cerr<<"SDL video error! "<<SDL_GetError()<<std::endl;
		exit(EXIT_FAILURE);
	}
}

void close_graphics()
// close out the graphics
{
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void init_images(int img_flags)
// initialize SDL_image
{
	if (!IMG_Init(img_flags)) {
		std::cerr<<"SDL image error! "<<IMG_GetError()<<std::endl;;
		exit(EXIT_FAILURE);
	}
}

void close_images()
// close out image library
{
	IMG_Quit();
}

void multimedia_start()
// start all multimedia
{
	init_images();
	init_graphics();
}

void multimedia_quit()
// close out all multimedia
{
	close_graphics();
	close_images();
	SDL_Quit();
}



