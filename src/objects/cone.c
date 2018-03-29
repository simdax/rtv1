#include "cone.h"
#include "rtv1.h"

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

int		cone_intersect(t_cone *cone, t_ray *hit, float *res)
{
  float	k;
  float	K;
  float	D_V;
  float	X_V;

  k = tan(cone->angle / 2);
  K = (1 + k * k);
  D_V = vec3f_dot(&hit->raydir, &cone->axis);
  X_V = vec3f_dot(&hit->distance, &cone->axis);
  return (resolveQuadratic((t_vec3f){
      vec3f_dot(&hit->raydir, &hit->raydir) - K * pow(D_V, 2),
	2 * (vec3f_dot(&hit->raydir, &hit->distance) - K * D_V * X_V),
	vec3f_dot(&hit->distance, &hit->distance) - K * pow(X_V, 2)
	}, res));
}

void		cone_normale(t_cone *cone, t_ray *hit)
{
  float		k;
  float		m;
  t_vec3f	tmp;

  tmp = cone->axis;
  vec3f_mul_unit2(&tmp, hit->tnear);
  k = tan(cone->angle / 2);
  m = vec3f_dot(&hit->raydir, &tmp) + vec3f_dot(&hit->distance, &cone->axis);
  tmp = cone->axis;
  vec3f_mul_unit2(&tmp, m);
  vec3f_mul_unit2(&tmp, (1+k*k));
  vec3f_sub2(&hit->nhit, &cone->tip_position);
  vec3f_sub2(&hit->nhit, &tmp);
}

void		cone_print(t_cone *cone)
{
  if (&cone->tip_position)
    {
      printf("position : ");
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
