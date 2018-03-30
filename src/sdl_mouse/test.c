#include "sdl_mouse.h"

int				main(int argc, char **args)
{
  t_main		m;
  SDL_Renderer	*renderer;
  t_texture	*textures;
	
  if (init(m.window, &renderer))
    {
      if (!(m.textures = textures_loader(1, renderer, "button.png")))
	return (0);
      m.buttons = buttons_loader(4, m.textures[0],
				 4, (SDL_Rect){0, 200, B_WTH, B_HGT},
				 0, 0, S_WTH - B_WTH, 0,
				 0, S_HGT - B_HGT, S_WTH - B_WTH, S_HGT - B_HGT
				 );
      m.quit = 0;
      while (!m.quit)
	events(&m, renderer);
    }
  Pclose(m.texture_button, m.window, renderer);
  return (0);
}
