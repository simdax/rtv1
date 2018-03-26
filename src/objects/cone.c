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

static int	cone_intersect2(t_ray *hit, t_cone *cone, float *res, float t1)
{
  float		h;
  t_vec3f	cp;
  t_vec3f	tmp;

  vec3f_cpy(&hit->cp, &hit->rayorig);
  vec3f_cpy(&tmp, &hit->raydir);
  vec3f_mul_unit2(&tmp, t1);
  vec3f_sub2(&tmp, &cone->tip_position);
  vec3f_add2(&hit->cp, &tmp);
  /* h = vec3f_dot(&hit->cp, &cone->axis); */
  /* if (h < 0 || h > cone->height) */
  /*   return (0); */
  *res = t1;
  return (1);  
}

int	cone_intersect(t_cone *cone, t_ray *hit, float *res)
{
  t_vec3f	co;
  t_vec3f	equation;
  float		det;
  float		t1;
  float		t2;

  vec3f_cpy(&co, &hit->rayorig);
  vec3f_sub2(&co, &cone->tip_position);
  equation = (t_vec3f){
    vec3f_dot(&hit->raydir, &cone->axis) * vec3f_dot(&hit->raydir, &cone->axis) - cone->angle2,
    2 * (vec3f_dot(&hit->raydir, &cone->axis) * vec3f_dot(&co, &cone->axis) - vec3f_dot(&hit->raydir, &co) * cone->angle2),
    vec3f_dot(&co, &cone->axis) * vec3f_dot(&co, &cone->axis) - vec3f_dot(&co, &co) * cone->angle2
  };
  det = equation.y * equation.y - 4 * equation.x * equation.z;
  if (det < BIAS)
    return (0);
  det = sqrt(det);
  t1 = (-equation.y - det) / (2 * equation.x);
  t2 = (-equation.y + det) / (2 * equation.x);
  if (t1 < 0 || t2 > 0 && t2 < t1)
    t1 = t2;
  if (t1 < BIAS)
    return (0);
  return (cone_intersect2(hit, cone, res, t1));
}

void	cone_normale(t_cone *cone, t_ray *hit)
{
  t_vec3f	n;
  t_vec3f	tmp;

  vec3f_cpy(&hit->phit, &hit->cp);
  vec3f_cpy(&hit->nhit, &hit->phit);
  vec3f_mul_unit2(&hit->nhit, vec3f_dot(&cone->axis, &hit->cp) / vec3f_dot(&hit->cp, &hit->cp));
  vec3f_sub2(&hit->nhit, &cone->axis);
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
