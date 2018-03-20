#include "rtv1.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
  int	color = 0;
  color = (int)(fmin(1.0, colors->z) * 255);
  color += (int)(fmin(1.0, colors->y) * 255) << 8;
  color += (int)(fmin(1.0, colors->x) * 255) << 16;
  pixel[index] = color;  
}

void	free_objs(t_obj **objects)
{
    /* while(*objects) */
    /*   free(*objects++); */
}

int	main(int argc, char **argv)
{
  t_obj	**objects;
  int		*screen;
  t_config	config;

  config = (t_config){1 / (float)WIDTH, 1 / (float)HEIGHT,
		      70, WIDTH / (float)HEIGHT, 0};
  config.angle = tan(M_PI * 0.5 * config.fov / 180.0);
  objects = configure(argv[1]);
  //objects = t(objects);
  screen = malloc(sizeof(int) * WIDTH * HEIGHT);
  render(&((t_render_opts){
      objects, screen, &config, &((t_vec3f){0, 0, 0})
    }));
  init_sdl(screen, objects, &config);
  free(screen);
  free_objs(objects);
  free(objects);
  return (0);
}
