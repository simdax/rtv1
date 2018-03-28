#include "cylinder.h"
//#include "rtv1.h"

t_cylinder	*cylinder_new(t_vec3f position, t_vec3f axis,
			      float radius)
{
  t_cylinder	*cyl;

  cyl = malloc(sizeof(t_cylinder));
  cyl->axis = axis;
  cyl->radius = radius;
  cyl->radius2 = radius * radius;
  return (cyl);
}

int	        cylinder_intersect(t_cylinder *cylinder, t_ray *hit,
				   float *res)
{
  return (resolveQuadratic ((t_vec3f){
  	vec3f_dot(&hit->raydir, &hit->raydir) - pow(vec3f_dot(&hit->raydir, &cylinder->axis), 2),
  	  2 * (vec3f_dot(&hit->raydir, &hit->distance) -
  	  vec3f_dot(&hit->raydir, &cylinder->axis) * vec3f_dot(&hit->distance, &cylinder->axis)),
  	  vec3f_dot(&hit->distance, &hit->distance) - pow(vec3f_dot(&hit->distance, &cylinder->axis), 2) - cylinder->radius2
  	  }, res));
}

/*    m = D|V*t + X|V */
/*    N = nrm( P-C-V*m ) */

void    	cylinder_normale(t_cylinder *cylinder, t_ray *hit)
{
  float		m;
  t_vec3f	tmp;

  tmp = cylinder->axis;
  vec3f_mul_unit2(&tmp, hit->tnear);
  m = vec3f_dot(&hit->raydir, &tmp)
    + vec3f_dot(&hit->distance, &cylinder->axis);
  tmp = cylinder->axis;
  vec3f_mul_unit2(&tmp, m);
  vec3f_sub2(&hit->nhit, &cylinder->position);
  vec3f_sub2(&hit->nhit, &tmp);
}

void		cylinder_print(t_cylinder *cylinder)
{
  printf("radius: %g\n", cylinder->radius);
  printf("axis:");
  vec3f_print(&cylinder->axis);
}
