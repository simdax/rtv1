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

inline void    plane_normale(t_plane *plane, t_ray *hit)
{
  vec3f_cpy(&hit->nhit, &plane->axis);
}

int	plane_intersect(t_plane *plane, t_ray *hit, float *res)
{
  t_vec3f	length;
  float		dot2;
  float		denom;
  
  denom = vec3f_dot(&plane->axis, &hit->raydir);
  if (denom > 0) {
    vec3f_cpy(&length, &plane->position);
    vec3f_sub2(&length, &hit->rayorig);
    dot2 = vec3f_dot(&length, &plane->axis) / denom;
    if (dot2 >= 0)
      {
	*res = dot2;
	return (1);
      }
    return (0);
  }
  return (0);
}
