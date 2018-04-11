#include "sdl_setup.h"

void		quit_SDL(t_sdl *sdl)
{
  SDL_DestroyTexture(sdl->texture);
  SDL_DestroyRenderer(sdl->renderer);
  SDL_DestroyWindow(sdl->window);
  SDL_Quit();    
}
void		hard_quit_SDL(t_sdl *sdl)
{
  const char	*error;

  error = SDL_GetError();
  if (ft_strcmp(error, ""))
    printf("error: %s\n", error);
  sdl->exit(sdl);
}

void		new_SDL(t_sdl *sdl, t_render_opts *opts, const char *title)
{
  SDL_Init(SDL_INIT_VIDEO);
  sdl->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
				 SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
  sdl->renderer = SDL_CreateRenderer(sdl->window, -1, 0);
  sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGB888,
				  SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
  sdl->quit = 0;
  sdl->error = hard_quit_SDL;
  sdl->exit = quit_SDL;
}

void		error_SDL(t_sdl *sdl)
{
  hard_quit_SDL(sdl);
  exit(1);
}
