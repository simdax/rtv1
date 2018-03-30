#include "rtv1.h"
#include "sdl.h"
#include "sdl_mouse.h"

static void	event_loop(t_render_opts *opts, t_sdl *sdl)
{
  if (sdl->event.type == SDL_QUIT || sdl->event.key.keysym.sym == SDLK_q)
    sdl->quit = 1;
  else if (sdl->event.type == SDL_KEYDOWN)
    {
      if (sdl->event.key.keysym.sym == SDLK_DOWN)
	opts->camorig.z += 1;
      else if (sdl->event.key.keysym.sym == SDLK_UP)
	opts->camorig.z -= 1;
      else if (sdl->event.key.keysym.sym == SDLK_RIGHT)
	opts->camorig.x += 1;
      else if (sdl->event.key.keysym.sym == SDLK_LEFT)
	opts->camorig.x -= 1;
      else if (sdl->event.key.keysym.sym == SDLK_KP_0)
	opts->camdir.y += 10;
      else if (sdl->event.key.keysym.sym == SDLK_KP_1)
	opts->camdir.y -= 10;
      else if (sdl->event.key.keysym.sym == SDLK_KP_2)
	opts->camdir.x += 10;
      else if (sdl->event.key.keysym.sym == SDLK_KP_3)
	opts->camdir.x -= 10;
      render(opts);
    }
}

static void	events(t_sdl *sdl, t_render_opts *opts, t_interface *m)
{
  while (!sdl->quit)
    {
      SDL_UpdateTexture(sdl->texture, NULL, opts->pixels, WIDTH * sizeof(int));
      SDL_WaitEvent(&(sdl->event));
      event_loop(opts, sdl);
      SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
      m->loop(m, sdl->renderer, &(sdl->event));
      /* SDL_RenderClear(sdl->renderer);
       * 
       * while (++m->i < 4)
       * 	m->buttons[m->i]->button_render(m->buttons[m->i], sdl->renderer);
       */
       SDL_RenderPresent(sdl->renderer); 
    }
}

int		load_interface(t_interface *m, t_sdl *sdl)
{
  if (!(m->textures = textures_loader(1, sdl->renderer, "assets/button.png")))
    sdl->error(sdl);
  if (!(m->buttons = buttons_loader(4, m->textures[0],
				    4, (SDL_Rect){0, 200, B_WTH, B_HGT},
				    0, 0, S_WTH - B_WTH, 0,
				    0, S_HGT - B_HGT, S_WTH - B_WTH, S_HGT - B_HGT
				    )))
    sdl->error(sdl);
  return (1);
}

void		init_sdl(t_render_opts *opts)
{
  t_sdl		*sdl;
  t_interface	*m;

  if(!(sdl = ft_memalloc(sizeof(*sdl))))
    EXIT_ERROR;
  m = interface_new();
  new_SDL(sdl, opts, "Ray Tracer");
  if(!(load_interface(m, sdl)))
    return ;
  events(sdl, opts, m);
}
