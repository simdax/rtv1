#include "cylinder.h"

t_cylinder	*cylinder_new(t_vec3f position, t_vec3f axis,
			      float radius)
{
  t_cylinder	*cyl;

  cyl = malloc(sizeof(t_cylinder));
  cyl->axis = axis;
  cyl->radius = radius;
  return (cyl);
}
void    	cylinder_normale(t_cylinder *cylinder, t_hit *hit)
{
}

int		cylinder_intersect(t_cylinder *cylinder, t_hit *hit,
				  float *t0)
{
  float a = pow(hit->raydir->x, 2) + pow(hit->raydir->y, 2);
  float b = 2 * hit->raydir->x * hit->rayorig->x  +
    2 * hit->raydir->y * hit->rayorig->y;
  float c = pow(hit->rayorig->x, 2) + pow(hit->rayorig->y, 2) - 1;
  float det = b * b - 4 * a * c;
  if (det < 0)
    return (0);
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
				&cylinder->position));
    /* float h = vec3f_dot(hit->cp, &->axis); */
  /* if (h < 0 || h > cone->height) */
  /*   return (0); */
  *t0 = t;
  return (1);
}

void		cylinder_print(t_cylinder *cylinder)
{
  printf("radius: %g\n", cylinder->radius);
  printf("axis:");
  vec3f_print(&cylinder->axis);
}
