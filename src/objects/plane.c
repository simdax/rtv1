#include "plane.h"
#include "rtv1.h"

t_plane	*plane_new(t_vec3f position, t_vec3f normale)
{
  t_plane	*plane;
  
  plane = malloc(sizeof(t_plane));
  plane->position = position;
  plane->axis = normale;
  return (plane);
}

void	plane_print(t_plane *plane)
{
  printf("normale :");
  vec3f_print(&plane->axis);
}

void    plane_normale(t_plane *plane, t_hit *hit)
{
  vec3f_cpy(hit->nhit, &plane->axis);
}

int	plane_intersect(t_plane *plane, t_hit *hit, float *t0)
{
  t_vec3f	length;
  float		coucou;
  float		denom;
  
  vec3f_normalize(&plane->axis);
  denom = vec3f_dot(&plane->axis, hit->raydir);
  if (denom > BIAS) {
    vec3f_cpy(&length, &plane->position);
    vec3f_sub2(&length, hit->rayorig);
    coucou = vec3f_dot(&length, &plane->axis) / denom;
    if (coucou >= 0)
      {
	*t0 = coucou;
	return (1);
      }
    return (0);
  }
  return (0);
}
