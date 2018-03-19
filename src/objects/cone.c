#include "cone.h"

void	cone_intersect(t_cone *cone, t_vec3f *orig, t_vec3f *dir)
{
  /* t_vec3f co = orig - cone->tip_position; */
  /* float dot2 = pow(vec3f_dot(dir, cone->axis), 2); */
  /* float a = dot2 - cone->angle2; */
  /* float b = 2 * (dot2 - vec3f_dot(dir, &co) * cone->angle2); */
  /* float c = pow(vec3f_dot(&co, &(cone->axis)), 2) - vec3f_dot(&co, &co) * cone->angle2; */
  /* float det = b*b - 4.*a*c; */
  
  /* if (det < 0) */
  /*   return (0); */
  /* det = sqrt(det); */
  /* *t0 = (-b - det) / (2 * a); */
  /* *t1 = (-b + det) / (2 * a); */
  /* // This is a bit messy; there ought to be a more elegant solution. */
  /* float t = *t0; */
  /* if (t < 0 || t1 > 0 && t1 < t) */
  /*   t = *t1; */
  /* if (t < 0) */
  /*   return (0); */
  /* t_vec3f cp = orig + t*dir - cone->tip_position; */
  /* float h = vec3f_dot(&cp, cone->axis); */
  /* if (h < 0 || h > cone->height) */
  /*   return (0); */
  /* return (1); */
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
