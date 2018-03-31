#include "plane.h"
//#include "rtv1.h"

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

int	plane_intersect(t_plane *plane, t_ray *hit, float *res)
{
  float		X_D;
  float		D_V;
  float		result;
  
  D_V = vec3f_dot(&plane->axis, &hit->raydir);
  if (D_V > 0) {
    X_D = vec3f_dot(&hit->distance, &plane->axis);
    result =  -X_D / D_V;
    if (result >= 0)
      {
	*res = result;
	return (1);
      }
    return (0);
  }
  return (0);
}

inline void    plane_normale(t_plane *plane, t_ray *hit)
{
  vec3f_cpy(&hit->nhit, &plane->axis);
}

