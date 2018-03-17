#include "rtv1.h"

void	event_loop(t_sphere **spheres, int *pixels, t_config *config, t_sdl *sdl)
{
  t_vec3f	dir;

  dir = (t_vec3f){0, 0, 0};
  if (sdl->event.type == SDL_QUIT || sdl->event.key.keysym.sym == SDLK_q)
    sdl->quit = 1;
  else if (sdl->event.type == SDL_KEYDOWN)
    {
      if (sdl->event.key.keysym.sym == SDLK_DOWN)
	dir.x += 10;
      else if (sdl->event.key.keysym.sym == SDLK_UP)
	dir.x -= 10;
      else if (sdl->event.key.keysym.sym == SDLK_RIGHT)
	dir.y += 10;
      else if (sdl->event.key.keysym.sym == SDLK_LEFT)
	dir.y -= 10;
      render(spheres, pixels, config, &dir);
    }     
}

void	events(t_sdl *sdl, int *pixels, t_sphere **spheres, t_config *config)
{
  while (!sdl->quit)
    {
      SDL_UpdateTexture(sdl->texture, NULL, pixels, WIDTH * sizeof(int));
      SDL_WaitEvent(&(sdl->event));
      event_loop(spheres, pixels, config, sdl);
      SDL_RenderClear(sdl->renderer);
      SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
      SDL_RenderPresent(sdl->renderer);
    }
}

void	init_sdl(int *pixels, t_sphere **spheres, t_config *config)
{
  t_sdl		sdl;

  SDL_Init(SDL_INIT_VIDEO);
  sdl = (t_sdl){
    SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED,
		     SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0),
    0, 0, 0
  };
  sdl.renderer = SDL_CreateRenderer(sdl.window, -1, 0);
  sdl.texture = SDL_CreateTexture(sdl.renderer, SDL_PIXELFORMAT_RGB888,
				  SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
  events(&sdl, pixels, spheres, config);
  SDL_DestroyTexture(sdl.texture);
  SDL_DestroyRenderer(sdl.renderer);
  SDL_DestroyWindow(sdl.window);
  SDL_Quit();  
}
