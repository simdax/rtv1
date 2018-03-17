#include "rtv1.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
  int	color = 0;
  color = (int)(fmin(1.0, colors->z) * 255);
  color += (int)(fmin(1.0, colors->y) * 255) << 8;
  color += (int)(fmin(1.0, colors->x) * 255) << 16;
  pixel[index] = color;  
}

void	render(t_sphere **spheres, int *pixel, t_config *config, t_vec3f *dir)
{
  t_vec3f	raydir;
  t_vec3f	color;
  unsigned	y;
  unsigned	x;
  
  y = 0;  
  while (y < HEIGHT)
    {
      x = 0;
      while (x < WIDTH)
    	{
    	  raydir = (t_vec3f){
	    (2 * ((x + 0.5) * config->invWidth) - 1) * config->angle * config->aspectratio,
	    (1 - 2 * ((y + 0.5) * config->invHeight)) * config->angle,
	    -1
	  };
    	  vec3f_normalize(&raydir);
	  trace(dir, &raydir, spheres, 0, &color);
    	  draw(pixel, (y * WIDTH) + x, &color);
    	  ++x;
    	}
      ++y;
    }
}

int	main(int argc, char **argv)
{
  t_sphere	**ptr;
  int		*pixels;
  t_config	config;

  config = (t_config){1 / (float)WIDTH, 1 / (float)HEIGHT,
		      70, WIDTH / (float)HEIGHT, 0};
  config.angle = tan(M_PI * 0.5 * config.fov / 180.0);
  ptr = configure("config");
  pixels = malloc(sizeof(int) * WIDTH * HEIGHT);
  render(ptr, pixels, &config, &((t_vec3f){0, 0, 0}));
  init_sdl(pixels, ptr);
  free(pixels);
  return (0);
}
