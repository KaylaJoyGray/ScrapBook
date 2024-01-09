#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <memory>

struct SDLw_delet
{
	void operator() (SDL_Window *wind);
	void operator() (SDL_Renderer *rend);
	void operator() (SDL_Texture *text);
	void operator() (SDL_Surface *surf);
	void operator() (SDL_Event *event);
};

using wind_ptr = std::unique_ptr<SDL_Window,SDLw_delet>;
using rend_ptr = std::unique_ptr<SDL_Renderer,SDLw_delet>;
using text_ptr = std::unique_ptr<SDL_Texture,SDLw_delet>;
using surf_ptr = std::shared_ptr<SDL_Surface>;

wind_ptr create_window(const char* title, int width, int height);

rend_ptr create_renderer(wind_ptr &wind, int index=-1, int flags=SDL_RENDERER_ACCELERATED);

void set_render_draw_color(rend_ptr &renderer, int r, int g, int b, int a);

void clear_render(rend_ptr &renderer);

void present_render(rend_ptr &renderer);

int render_texture(text_ptr &texture, rend_ptr &renderer);

int render_texture(text_ptr &texture, rend_ptr &renderer, SDL_Rect &src, SDL_Rect &dest);

text_ptr load_texture(const char *file_path, rend_ptr &renderer);

int init_graphics();

void close_graphics();

int init_images(int img_flags=IMG_INIT_PNG);

void close_images();

void multimedia_quit();

#endif
