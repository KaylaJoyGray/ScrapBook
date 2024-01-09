/*
 * rendering.cpp
 * 
 */

#include "rendering.h"
#include <iostream>

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

using wind_ptr = std::unique_ptr<SDL_Window,SDLw_delet>;
using rend_ptr = std::unique_ptr<SDL_Renderer,SDLw_delet>;
using text_ptr = std::unique_ptr<SDL_Texture,SDLw_delet>;
using surf_ptr = std::shared_ptr<SDL_Surface>;

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
					SDL_WINDOW_FULLSCREEN_DESKTOP
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

int render_texture(text_ptr &texture, rend_ptr &renderer, SDL_Rect &src, SDL_Rect &dest)
// renders a texture with src and dest rectangles
{
	return SDL_RenderCopy(renderer.get(), texture.get(), &src, &dest);
}

text_ptr load_texture(const char *file_path, rend_ptr &renderer)
// returns a unique pointer to a texture loaded from image file
{
	text_ptr result;
	
	surf_ptr loaded_surface(IMG_Load(file_path), SDLw_delet());
	
	if (loaded_surface == nullptr) {
		std::cerr<<"SDL image error! "<<IMG_GetError()<<std::endl;
	} else {
		result = text_ptr(SDL_CreateTextureFromSurface(renderer.get(), loaded_surface.get()));
	}
	
	return result;
}

int init_graphics()
// initialize SDL Video
{
	int gflag = 0; 
	if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
		std::cerr<<"SDL video error! "<<SDL_GetError()<<std::endl;
		gflag = -1;
	}
	return gflag;
}

void close_graphics()
// close out the graphics
{	
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

int init_images(int img_flags)
// initialize SDL_image
{
	int iflag = 0;
	if (!IMG_Init(img_flags)) {
		std::cerr<<"SDL image error! "<<IMG_GetError()<<std::endl;;
		iflag = -1;
	}
	return iflag;
}

void close_images()
// close out image library
{
	IMG_Quit();
}

void multimedia_quit()
// close out all multimedia
{
	close_graphics();
	close_images();
	SDL_Quit();
}



