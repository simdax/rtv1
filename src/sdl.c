#include "rtv1.h"

void	events(SDL_Window *window, SDL_Texture *texture,
	       SDL_Renderer *renderer, unsigned long *pixels[WIDTH * HEIGHT])
{
  int quit = 0;
  SDL_Event event;
  while (!quit)
    {
      SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(unsigned long));
      SDL_WaitEvent(&event);
      switch (event.type)
        {
        case SDL_QUIT:
	  quit = 1;
	  break;
        }
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
}

void	init_sdl()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("SDL2 Pixel Drawing",
					 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture *texture = SDL_CreateTexture(renderer,
					    SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
  unsigned long	*pixels[WIDTH * HEIGHT]; 
  memset(pixels, 255, 640 * 480 * sizeof(unsigned long));
  events(window, texture, renderer, pixels);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();  
}
