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

void test(t_sphere *a, t_sphere *b)
{
  sphere_print(a);
  printf("\nET\n");
  sphere_print(b);
}

int main(int argc, char **argv)
{
  t_sphere *spheres[7];
  t_sphere **ptr;
  int	pixels[WIDTH * HEIGHT];
  int 	*pixel = pixels;

  ptr = configure("config");
  render(ptr, pixel);
  init_sdl(pixel);
  return (0);
}
