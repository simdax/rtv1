#include "plane.h"

t_plane	*plane_new(t_vec3f position, t_vec3f normale)
{
  t_plane	*plane;
  
  plane = malloc(sizeof(t_plane));
  plane->position = position;
  plane->normale = normale;
  return (plane);
}

void		plane_print(t_plane *plane)
{
  printf("normale :");
  vec3f_print(&plane->normale);
}

void    plane_normale(t_plane *plane, t_hit *hit)
{
  vec3f_cpy(hit->nhit, &plane->normale);
}

int	plane_intersect(t_plane *plane, t_hit *hit, float *t0)
{
  t_vec3f n = (t_vec3f){-0.5, -2, -0.5};
  vec3f_normalize(&n);
  float denom = vec3f_dot(&n, hit->raydir);
  if (denom > 1e-6) {
    //    printf("fdsf");
    t_vec3f p0l0 = plane->position;
    vec3f_sub(&p0l0, hit->rayorig);
    *t0 = vec3f_dot(&p0l0, &n) / denom;
    return (*t0 >= 0);
  }
  return (0);
}
