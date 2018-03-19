#include "sphere.h"

t_sphere	*sphere_new(t_vec3f center,
			    t_vec3f surface_color,
			    t_vec3f emission_color,
			    t_sphere_infos infos)
{
  t_sphere	*ret = malloc(sizeof(t_sphere));
  
  ret->center = center;
  ret->radius = infos.radius;
  ret->radius2 = infos.radius * infos.radius;
  ret->surface_color = surface_color;
  ret->emission_color = emission_color;
  ret->transparency = infos.transparency;
  ret->reflection = infos.reflection;
  return (ret);
}

int		plane_intersect(t_sphere *sphere,
				t_vec3f *orig, t_vec3f *dir,
				float *t0, float *t1)
{
  (void)t1;
  t_vec3f n = (t_vec3f){-0.5, -2, -0.5};
  vec3f_normalize(&n);
  float denom = vec3f_dot(&n, dir);
  if (denom > 1e-6) {
    //    printf("fdsf");
    t_vec3f p0l0 = sphere->center;
    vec3f_sub(&p0l0, orig);
    *t0 = vec3f_dot(&p0l0, &n) / denom;
    return (*t0 >= 0);
  }
  return (0);
}

/* int	sphere_intersect(t_sphere *sphere, */
/* 			 t_vec3f *eye, t_vec3f *vector, */
/* 			 float *t0, float *t1) */
/* { */
/*   double	a; */
/*   double	b; */
/*   double	c; */
/*   double	delta; */
  
/*   a = pow(vector->x, 2) + pow(vector->y, 2); */
/*   b = 2 * (eye->x * vector->x + eye->y * vector->y); */
/*   c = pow(eye->x, 2) + pow(eye->y, 2) - pow(R / 1.5, 2); */
/*   delta = pow(b, 2) - 4 * a * c; */
/*   *t0 = (delta >= 0 ? (-b - sqrt(delta)) / (2 * a) : -1); */
/*   *t1 = (delta >= 0 ? (-b + sqrt(delta)) / (2 * a) : -1); */
/* } */

int		sphere_intersect(t_sphere *sphere,
				  t_vec3f *rayorig, t_vec3f *raydir,
				  float *t0, float *t1)
{
  float		thc;
  float		tca;
  float		d2;
  t_vec3f	l;

  vec3f_cpy(&l, &sphere->center);
  vec3f_sub2(&l, rayorig);
  tca = vec3f_dot(&l, raydir);
  if (tca < 0)
    return (0);
  d2 = vec3f_dot(&l, &l) - tca * tca;
  if (d2 > sphere->radius2)
    return (0);
  thc = sqrt(sphere->radius2 - d2);
  *t0 = tca - thc;
  *t1 = tca + thc;
  return (1);
}

void	sphere_normale(t_sphere *sphere, t_vec3f *raydir,
		       t_vec3f *rayorig, float *tnear,
		       t_vec3f *nhit, t_vec3f *phit)
{
  t_vec3f	tmp;

  vec3f_cpy(&tmp, raydir);
  vec3f_cpy(phit, rayorig);
  vec3f_mul_unit2(&tmp, *tnear);
  vec3f_add2(phit, &tmp);
  vec3f_cpy(nhit, phit);
  vec3f_sub2(nhit, &(sphere->center));
  vec3f_normalize(nhit);  
}

void		sphere_print(t_sphere *sphere)
{
  if (&sphere->center)
    {
      printf("centre : ");
      vec3f_print(&sphere->center);
    }
  printf("radius : %g\n ///////\n", sphere->radius);
}
