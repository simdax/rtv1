#include "rtv1.h"

void	event_loop(t_render_opts *opts, t_sdl *sdl)
{
  if (sdl->event.type == SDL_QUIT || sdl->event.key.keysym.sym == SDLK_q)
    sdl->quit = 1;
  else if (sdl->event.type == SDL_KEYDOWN)
    {
      if (sdl->event.key.keysym.sym == SDLK_DOWN)
	opts->dir->z += 1;
      else if (sdl->event.key.keysym.sym == SDLK_UP)
	opts->dir->z -= 1;
      else if (sdl->event.key.keysym.sym == SDLK_RIGHT)
	opts->dir->x += 1;
      else if (sdl->event.key.keysym.sym == SDLK_LEFT)
	opts->dir->x -= 1;
      //      printf("%f %f %f\n", opts->dir->x, opts->dir->y, opts->dir->z); fflush(stdout);
      render(opts);
    }     
}

void	events(t_sdl *sdl, int *screen, t_sphere **objects, t_config *config)
{
  t_vec3f	dir;

  dir = (t_vec3f){0, 0, 0};
  while (!sdl->quit)
    {
      SDL_UpdateTexture(sdl->texture, NULL, screen, WIDTH * sizeof(int));
      SDL_WaitEvent(&(sdl->event));
      event_loop(&((t_render_opts){
	    objects, screen, config, &dir
	  }), sdl);
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
