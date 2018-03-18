#include "rtv1.h"

void	*render_f(void *render_opts)
{
  t_vec3f	raydir;
  t_vec3f	color;
  unsigned	y;
  unsigned	x;
  t_render_opts	*opts;

  opts = ((t_thread*)render_opts)->opts;
  y = ((t_thread*)render_opts)->from;
  while (y < ((t_thread*)render_opts)->to)
    {
      x = 0;
      while (x < WIDTH)
    	{
    	  raydir = (t_vec3f){
	    (2 * ((x + 0.5) * opts->config->invWidth) - 1) * opts->config->angle * opts->config->aspectratio,
	    (1 - 2 * ((y + 0.5) * opts->config->invHeight)) * opts->config->angle,
	    -1
	  };
    	  vec3f_normalize(&raydir);
	  trace(opts->dir, &raydir, opts->spheres, 0, &color);
    	  draw(opts->pixels, (y * WIDTH) + x, &color);
    	  ++x;
    	}
      ++y;
    }
  pthread_exit(0);
}

int     render(t_render_opts *opts)
{
  pthread_t     	*threads;
  t_thread	     	*args;
  int                   i;
  int                   u;
  
  if (!(threads = malloc(sizeof(pthread_t) * 8)))
    return (0);
  if (!(args = malloc(sizeof(t_thread) * 8)))
    return (0);
  i = 0;
  while (i < 8)
    {
      args[i] = (t_thread){(HEIGHT * i) / 8, (HEIGHT * (i + 1)) / 8, i, opts};
      u = pthread_create(&threads[i], NULL, render_f, &(args[i]));
      ++i;
    }
  i = 0;
  while (i < 8)
    pthread_join(threads[i++], NULL);
  free(threads);
  free(args);
  return (1);
}
