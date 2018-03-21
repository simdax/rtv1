#include "cylinder.h"

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
  
  /* vec3f_cpy(&tmp, hit->raydir); */
  /* vec3f_cpy(hit->phit, hit->rayorig); */
  /* vec3f_mul_unit2(&tmp, *hit->tnear); */
  /* vec3f_add2(hit->phit, &tmp); */
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
    int ACC = 0;

    a = hit->raydir->x * hit->raydir->x + hit->raydir->z * hit->raydir->z;
    b = 2 * hit->raydir->x * (hit->rayorig->x - cylinder->position.x) + 2 * hit->raydir->z * (hit->rayorig->z - cylinder->position.z);
    c = (hit->rayorig->x - cylinder->position.x) * (hit->rayorig->x - cylinder->position.x) + (hit->rayorig->z - cylinder->position.z) * (hit->rayorig->z - cylinder->position.z) - cylinder->radius * cylinder->radius;

    delta = b * b - 4 * a * c;
    if (delta > ACC)
    {
            root = (-1 * b - sqrt(delta)) / 2 * a - ACC;
            if (root <= ACC)
                    root = (-1 * b + sqrt(delta)) / 2 * a - ACC;
	    *t0 = root;
            return (1);
    }
    return (0);
}

/* int		cylinder_intersect(t_cylinder *cylinder, t_hit *hit, */
/* 				  float *t0) */
/* { */
/*   t_vec3f *yes = vec3f_sub(hit->raydir, */
/* 			   vec3f_mul_unit(&cylinder->axis, */
/* 					   vec3f_dot(hit->raydir, &cylinder->axis))); */
/*   t_vec3f *deltap = vec3f_sub(hit->rayorig, &cylinder->position); */
/*   t_vec3f *yo = vec3f_sub(deltap, */
/* 			  vec3f_mul_unit(&cylinder->axis, */
/* 					 vec3f_dot(deltap, &cylinder->axis) */
/* 					 ));  */
/*   float a = vec3f_dot(yes, yes); */
/*   float b = 2 * (vec3f_dot(yes, yo)); */
/*   float c = vec3f_dot(yo, yo) - cylinder->radius2; */
/*   float det = b * b - 4 * a * c; */
/*   if (det < 0) */
/*     return (0); */
/*   float t1 = (-b - det) / (2. * a); */
/*   float t2 = (-b + det) / (2. * a); */
/*   // This is a bit messy; there ought to be a more elegant solution. */
/*   float t = t1; */
/*   if (t < 0 || t2 > 0 && t2 < t) */
/*     t = t2; */
/*   if (t < 0) */
/*     return (0); */
/*     hit->cp =  vec3f_add(hit->rayorig, */
/* 			 vec3f_sub(vec3f_mul_unit(hit->raydir, t), */
/* 				   &cylinder->position)); */
/*     /\* float h = vec3f_dot(hit->cp, &->axis); *\/ */
/*   /\* if (h < 0 || h > cone->height) *\/ */
/*   /\*   return (0); *\/ */
/*   *t0 = t; */
/*   return (1); */
/* } */

void		cylinder_print(t_cylinder *cylinder)
{
  printf("radius: %g\n", cylinder->radius);
  printf("axis:");
  vec3f_print(&cylinder->axis);
}
