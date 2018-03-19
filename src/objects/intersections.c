#include "object.h"

/* Hit intersectPlane(Plane p, Ray r) */
/* { */
/*     float dotnd = dot(p.n, r.d); */
/*     if (dotnd > 0.) return noHit; */

/*     float t = -(dot(r.o, p.n) + p.d) / dotnd; */
/*     return Hit(t, p.n, p.m); */
/* } */

/* Hit intersectSphere(Sphere s, Ray r) */
/* { */
/* 	vec3 op = s.p - r.o; */
/*     float b = dot(op, r.d); */
/*     float det = b * b - dot(op, op) + s.r * s.r; */
/*     if (det < 0.) return noHit; */

/*     det = sqrt(det); */
/*     float t = b - det; */
/*     if (t < 0.) t = b + det; */
/*     if (t < 0.) return noHit; */

/*     return Hit(t, (r.o + t*r.d - s.p) / s.r, s.m); */
/* } */


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
  /* *t1 = (-b + det) / (2 * a);   */
  /* // This is a bit messy; there ought to be a more elegant solution. */
  /* float t = *t0; */
  /* if (t < 0 || t1 > 0 && t1 < t) */
  /*   t = *t1; */
  /* if (t < 0) */
  /*   return (0); */
  /* t_vec3f cp = orig + t*dir - cone->tip_position;  */
  /* float h = vec3f_dot(&cp, cone->axis); */
  /* if (h < 0 || h > cone->height) */
  /*   return (0); */
  /* return (1); */
}

void	cone_normale(t_cone *cone)
{
  //  t_vec3f n = normalize(cp * dot(s.v, cp) / dot(cp, cp) - s.v);
}
