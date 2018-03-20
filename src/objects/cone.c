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

int	cone_intersect(t_cone *cone, t_hit *hit, float *t0)
{
  t_vec3f *co = vec3f_sub(hit->rayorig, &cone->tip_position);
  float a = vec3f_dot(hit->raydir, &cone->axis) * vec3f_dot(hit->raydir, &cone->axis) - cone->angle2;
  float b = 2 * (vec3f_dot(hit->raydir, &cone->axis) * vec3f_dot(co, &cone->axis) - vec3f_dot(hit->raydir, co) * cone->angle2);
  float c = vec3f_dot(co, &cone->axis) * vec3f_dot(co, &cone->axis) - vec3f_dot(co, co) * cone->angle2;
  float det = b * b - 4 * a * c;
  if (det < 0)
    return (0);
  det = sqrt(det);
  float t1 = (-b - det) / (2. * a);
  float t2 = (-b + det) / (2. * a);
  // This is a bit messy; there ought to be a more elegant solution.
  float t = t1;
  if (t < 0 || t2 > 0 && t2 < t)
    t = t2;
  if (t < 0)
    return (0);
  hit->cp =  vec3f_add(hit->rayorig,
  		      vec3f_sub(vec3f_mul_unit(hit->raydir, t),
		      &cone->tip_position));
  float h = vec3f_dot(hit->cp, &cone->axis);
  if (h < 0 || h > cone->height)
    return (0);
  *t0 = t;
  return (1);
}

void	cone_normale(t_cone *cone, t_hit *hit)
{
  t_vec3f	n;
  t_vec3f	tmp;

  vec3f_cpy(hit->phit, hit->cp);
  vec3f_cpy(hit->nhit, hit->phit);
  vec3f_mul_unit2(hit->nhit, vec3f_dot(&cone->axis, hit->cp) /
		  vec3f_dot(hit->cp, hit->cp));
  vec3f_sub2(hit->nhit, &cone->axis);
  vec3f_normalize(hit->nhit);
}

void	        cone_print(t_cone *cone)
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
