#include "vec3f.h"
#include "SDL.h"

typedef struct	{
  t_vec3f	position;
  t_vec3f	axis;
}

void	debug(int *pixels)
{
  SDL_RenderDrawLine(SDL_Renderer* renderer, 0, 10, 0, 10);
 
}
