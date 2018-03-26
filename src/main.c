#include "rtv1.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
  int	color;

  color = 0;
  color = (int)(fmin(1.0, colors->z) * 255);
  color += (int)(fmin(1.0, colors->y) * 255) << 8;
  color += (int)(fmin(1.0, colors->x) * 255) << 16;
  pixel[index] = color;  
}

void	free_objs(t_obj ***objects)
{
  t_obj	**objs;

  objs = *objects;
  while(*objs)
    free(*objs++);
  free(*objects);
}

int	main(int argc, char **argv)
{
  t_obj		**objects;
  int		*screen;
  t_config	config;
  t_render_opts	opts;
  
  config = (t_config){1 / (float)WIDTH, 1 / (float)HEIGHT,
		      70, WIDTH / (float)HEIGHT, 0};
  config.angle = tan(M_PI * 0.5 * config.fov / 180.0);
  objects = configure(argv[1]);
  screen = malloc(sizeof(int) * WIDTH * HEIGHT);
  opts = (t_render_opts){
    objects, screen, &config, (t_vec3f){0, 0, 0}, (t_vec3f){0, 0, 0}
  };
  render(&opts);
  init_sdl(screen, objects, &config);
  free(screen);
  free_objs(&objects);
  return (0);
}
