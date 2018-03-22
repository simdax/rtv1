#include "cylinder.h"
#include "rtv1.h"

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

void    	cylinder_normale(t_cylinder *cylinder, t_hit *hit)
{
  t_vec3f	tmp;
  
  vec3f_cpy(hit->nhit, hit->phit);
  vec3f_sub2(hit->nhit, &(cylinder->axis));
  vec3f_normalize(hit->nhit);  
}

int	        cylinder_intersect(t_cylinder *cylinder, t_hit *hit,
 				  float *t0)
{
    double a;
    double b;
    double c;
    double delta;
    double root;

    a = hit->raydir->x * hit->raydir->x + hit->raydir->z * hit->raydir->z;
    b = 2 * hit->raydir->x * (hit->rayorig->x - cylinder->position.x) + 2 * hit->raydir->z * (hit->rayorig->z - cylinder->position.z);
    c = (hit->rayorig->x - cylinder->position.x) * (hit->rayorig->x - cylinder->position.x) + (hit->rayorig->z - cylinder->position.z) * (hit->rayorig->z - cylinder->position.z) - cylinder->radius * cylinder->radius;

    delta = b * b - 4 * a * c;
    if (delta > BIAS)
    {
            root = (-1 * b - sqrt(delta)) / 2 * a - BIAS;
            if (root <= BIAS)
                    root = (-1 * b + sqrt(delta)) / 2 * a - BIAS;
	    *t0 = root;
            return (1);
    }
    return (0);
}

void		cylinder_print(t_cylinder *cylinder)
{
  printf("radius: %g\n", cylinder->radius);
  printf("axis:");
  vec3f_print(&cylinder->axis);
}
