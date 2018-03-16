#include "rtv1.h"

void	draw(int *pixel, int index, t_vec3f *colors)
{
  int color = 0;
  color = (int)(fmin(1.0, colors->z) * 255);
  color += (int)(fmin(1.0, colors->y) * 255) << 8;
  color += (int)(fmin(1.0, colors->x) * 255) << 16;
  pixel[index] = color;  
}

void	render(t_sphere **spheres, int *pixel)
{
  float invWidth = 1 / (float)WIDTH, invHeight = 1 / (float)HEIGHT;  
  float fov = 70, aspectratio = WIDTH / (float)HEIGHT;
  float angle = tan(M_PI * 0.5 * fov / 180.0);
  unsigned y = 0;
    while (y < HEIGHT)
    {
      unsigned x = 0;
      while (x < WIDTH)
    	{
    	  float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
    	  float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
    	  t_vec3f *raydir = vec3f_new(xx, yy, -1);
    	  vec3f_normalize(raydir);
    	  draw(pixel, (y * WIDTH) + x, trace(vec3f_new(0, 0, 0), raydir, spheres, 0));
    	  ++x;
    	}
      ++y;
    }
}

int main(int argc, char **argv)
{
  t_sphere *spheres[7];
  t_sphere **ptr = spheres;
  int	pixels[WIDTH * HEIGHT];
  int 	*pixel = pixels;

  //  parse("config");
  spheres[0] = sphere_new(vec3f_new(0.0, -10004, -20), vec3f_new(0.20, 0.20, 0.20),
  			  vec3f_new_unit(0), (t_sphere_infos){10000, 0, 0.0});
  spheres[1] = sphere_new(vec3f_new(0.0, 0, -20), vec3f_new(1.00, 0.32, 0.36),
  			  vec3f_new_unit(0), (t_sphere_infos){4, 1, 0.5});
  spheres[2] = sphere_new(vec3f_new(5.0, -1, -15), vec3f_new(0.90, 0.76, 0.46),
  			  vec3f_new_unit(0.1), (t_sphere_infos){2, 1, 0.5});
  spheres[3] = sphere_new(vec3f_new(5, 0, -25), vec3f_new(0.65, 0.77, 0.97),
  			  vec3f_new_unit(0), (t_sphere_infos){3, 1, 0.0});
  spheres[4] = sphere_new(vec3f_new(-5.5, 0, -15), vec3f_new(0.90, 0.90, 0.90),
  			  vec3f_new_unit(0), (t_sphere_infos){3, 1, 0.0});
  // light
  spheres[5] = sphere_new(vec3f_new(0.0, 20, -30), vec3f_new_unit(0),
  			  vec3f_new_unit(3), (t_sphere_infos){1, 0, 0.0});
  spheres[6] = 0;
  render(ptr, pixel);
  init_sdl(pixel);
  return (0);
}
