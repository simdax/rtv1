#include "rtv1.h"

#define WIDTH	640
#define HEIGHT  480

void	draw(t_vec3f image[WIDTH * HEIGHT])
{
  FILE * fp;
  
  fp = fopen ("untitled.ppm", "wb+");
  fprintf(fp, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
  for (unsigned i = 0; i < WIDTH * HEIGHT; ++i)
    {
      static unsigned color[3];
      color[0] = (unsigned char)(fmin(1.0, image[i].x) * 255);
      color[1] = (unsigned char)(fmin(1.0, image[i].y) * 255);
      color[2] = (unsigned char)(fmin(1.0, image[i].z) * 255);
      fwrite(color, 1, 3, fp);
    }
}

void	render(t_sphere **spheres)
{
  t_vec3f image[WIDTH * HEIGHT];
  t_vec3f *pixel = image;
  float invWidth = 1 / (float)WIDTH, invHeight = 1 / (float)HEIGHT;
  float fov = 30, aspectratio = WIDTH / (float)HEIGHT;
  float angle = tan(M_PI * 0.5 * fov / 180.0);
  for (unsigned y = 0; y < HEIGHT; ++y) {
    for (unsigned x = 0; x < WIDTH; ++x) {
      float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
      float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
      t_vec3f *raydir = vec3f_new(xx, yy, -1);
      vec3f_normalize(raydir);
      *pixel = *(trace(vec3f_new_unit(0), raydir, spheres, 0));
      ++pixel;
    }
  }
  draw(image);
}

int main(int argc, char **argv)
{
  t_sphere *spheres[7];
  t_sphere **ptr = spheres;

  spheres[0] = sphere_new(vec3f_new(0.0, -10004, -20), vec3f_new(0.20, 0.20, 0.20),
			  vec3f_new_unit(0), (t_sphere_infos){10000, 0, 0.0});
  spheres[1] = sphere_new(vec3f_new(0.0, 0, -20), vec3f_new(1.00, 0.32, 0.36),
			  vec3f_new_unit(0), (t_sphere_infos){4, 1, 0.5});
  spheres[2] = sphere_new(vec3f_new(5.0, -1, -15), vec3f_new(0.90, 0.76, 0.46),
			  vec3f_new_unit(0), (t_sphere_infos){2, 1, 0.0});
  spheres[3] = sphere_new(vec3f_new(-5.5, 0, -25), vec3f_new(0.65, 0.77, 0.97),
			  vec3f_new_unit(0), (t_sphere_infos){3, 1, 0.0});
  spheres[4] = sphere_new(vec3f_new(0.0, 0, -15), vec3f_new(0.90, 0.90, 0.90),
			  vec3f_new_unit(0), (t_sphere_infos){3, 1, 0.0});
  // light
  spheres[5] = sphere_new(vec3f_new(50.0, -10, 30), vec3f_new_unit(0),
			  vec3f_new_unit(3), (t_sphere_infos){3, 0, 0.0});
  spheres[6] = 0;
  render(ptr);
  return (0);
}
