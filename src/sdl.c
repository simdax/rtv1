#include "rtv1.h"

void	events(SDL_Window *window, SDL_Texture *texture,
	       SDL_Renderer *renderer, int pixels[WIDTH * HEIGHT])
{
  int quit = 0;
  SDL_Event event;
  while (!quit)
    {
      SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(int));
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
  SDL_Window *window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
					   SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
  int	pixels[WIDTH * HEIGHT];
  for (int i = 0; i < WIDTH * HEIGHT; ++i )
    {
      //      int color = 
      pixels[i] = 27 + (25 << 8) + (126 << 16);
      //      memset(pixels + i, 127, sizeof(*pixels));
      /* pixels[i] += 224 << 2; */
      /* pixels[i] += 024 << 4; */
    }
  events(window, texture, renderer, pixels);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();  
}
