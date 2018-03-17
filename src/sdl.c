#include "rtv1.h"

void	events(SDL_Window *window, SDL_Texture *texture,
	       SDL_Renderer *renderer, int pixels[WIDTH * HEIGHT], t_sphere **spheres)
{
  int quit = 0;
  t_vec3f dir = (t_vec3f){0, 0, 0};
  SDL_Event event;

  //  srand(time(0));
  while (!quit)
    {
      SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(int));
      SDL_WaitEvent(&event);
      switch (event.type)
        {
        case SDL_QUIT:
	    quit = 1;
	    break;
	case SDL_KEYDOWN:
	  switch (event.key.keysym.sym)
	    {
	    case SDLK_q:
	      quit = 1;
	      break;
	    case SDLK_LEFT:
	      dir.y += 10;
	      render(spheres, pixels, &dir);
	    case SDLK_RIGHT:
	      dir.y -= 10;
	      render(spheres, pixels, &dir);
	    case SDLK_UP:
	      dir.x += 10;
	      render(spheres, pixels, &dir);
	    case SDLK_DOWN:
	      dir.x -= 10;
	      render(spheres, pixels, &dir);
	      break;
	    }
	  break;
        }
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
    }
}

void	init_sdl(int *pixels, t_sphere **spheres)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888,
					   SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
  events(window, texture, renderer, pixels, spheres);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();  
}
