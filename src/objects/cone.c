#include "cone.h"

t_cone	*cone_new(float angle, float height,
		  t_vec3f tip_position, t_vec3f	axis)
{
  t_cone	*cone;

  cone = malloc(sizeof(t_cone));
  cone->angle = angle;
  cone->angle2 = angle * angle;
  cone->height = height;
  cone->tip_position = tip_position;
  cone->axis = axis;
}

int	cone_intersect(t_cone *cone, t_vec3f *orig, t_vec3f *dir, float *t0)
{
  float a = pow(dir->x, 2) + pow(dir->y, 2) - pow(dir->z, 2);
  float b = (2 * orig->x * dir->x) + (2 * orig->y * dir->y) - (2 * orig->z * dir->z);
  float c = pow(orig->x, 2) + pow(orig->y, 2) - pow(orig->z, 2);
  float z0 = (-b - sqrt(pow(b, 2) - 4 * a * c )) / 2 * a;
  float z1 = (-b + sqrt(pow(b, 2) - 4 * a * c )) / 2 * a;
  if (z1 < 0)
    return (0);
  if ((*t0 = z0) < 0)
      *t0 = z1;
  return (1);
}

void	cone_normale(t_cone *cone, t_hit *hit)
{
  t_vec3f	n;
  t_vec3f	tmp;

  /* vec3f_cpy(&tmp, hit->phit); */
  /* vec3f_mul2(&tmp, vec3f_dot(&cone->axis, cp) / vec3f_dot(cp, cp)); */
  /* vec3f_sub2(&tmp, &cone->axis); */
  /* vec3f_normalize(hit->nhit); */
}


void	        cone_print(t_cone *cone)
{
  if (&cone->tip_position)
    {
      printf("pos : ");
      vec3f_print(&cone->tip_position);
    }
  if (&cone->axis)
    {
      printf("axis : ");
      vec3f_print(&cone->axis);
    }
  printf("angle : %g\n", cone->angle);
  printf("height : %g\n", cone->height);
}
