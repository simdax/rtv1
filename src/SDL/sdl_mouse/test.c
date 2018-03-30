#include "sdl_mouse.h"

void		        events(t_interface *m, SDL_Renderer *renderer);
void			Pclose(SDL_Window *window, SDL_Renderer *renderer);
int			init(SDL_Window *window, SDL_Renderer **renderer);
void			free_buttons(t_interface *m);

int				main(int argc, char **args)
{
  t_interface		*m;
  SDL_Renderer	*renderer;
  t_texture	*textures;

  m = interface_new();
  if (init(m->window, &renderer))
    {
      if (!(m->textures = textures_loader(1, renderer, "button.png")))
	return (0);
      if (!(m->buttons = buttons_loader(4, m->textures[0],
				       4, (SDL_Rect){0, 200, B_WTH, B_HGT},
				       0, 0, S_WTH - B_WTH, 0,
				       0, S_HGT - B_HGT, S_WTH - B_WTH, S_HGT - B_HGT
				       )))
	return (0);
      m->quit = 0;
      while (!m->quit)
	m->loop(m, renderer);
    }
  Pclose(m->window, renderer);
  interface_free(m);
  return (0);
}
