#include "rtv1.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
  int	color = 0;
  color = (int)(fmin(1.0, colors->z) * 255);
  color += (int)(fmin(1.0, colors->y) * 255) << 8;
  color += (int)(fmin(1.0, colors->x) * 255) << 16;
  pixel[index] = color;  
}

t_sphere **t(t_sphere **s){
  t_sphere **spheres = malloc(sizeof(t_sphere*) * 20);
  //  parse("config");
  /* spheres[0] = sphere_new((t_vec3f){0.0, -10004, -20}, (t_vec3f){0.20, 0.20, 0.20}, */
  /* 			  (t_vec3f){0, 0, 0}, (t_sphere_infos){10000, 0, 0.0}); */
  spheres[0] = sphere_new((t_vec3f){0.0, 0, -20}, (t_vec3f){1.00, 0.32, 0.36},
  			  (t_vec3f){0, 0, 0}, (t_sphere_infos){4, 1, 0.5});
  /* spheres[2] = sphere_new((t_vec3f){5, -1, -15}, (t_vec3f){0.9, 0.76, 0.46}, */
  /* 			  (t_vec3f){0, 0, 0}, (t_sphere_infos){2, 1, 0.5}); */
  /* spheres[3] = sphere_new((t_vec3f){5, 0, -25}, (t_vec3f){0.65, 0.77, 0.97}, */
  /* 			  (t_vec3f){0, 0, 0}, (t_sphere_infos){3, 1, 0.0}); */
  /* spheres[4] = sphere_new((t_vec3f){-5.5, 0, -15}, (t_vec3f){0.90, 0.90, 0.90}, */
  /* 			  (t_vec3f){0, 0, 0}, (t_sphere_infos){3, 1, 0.0}); */
  /* spheres[5] = sphere_new((t_vec3f){0.0, 20, -30}, (t_vec3f){0, 0, 0}, */
  /* 			  (t_vec3f){3, 3, 3}, (t_sphere_infos){1, 0, 0.0}); */
  spheres[1] = 0;

/*   int i; */
/*   for (int i =0 ; i < 7; ++i) */
/*     {    //sphere_print(spheres[i]); */
/*         sphere_print(s[i]); */
/* } */
  return (spheres);
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
