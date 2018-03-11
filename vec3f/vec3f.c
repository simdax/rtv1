#include "vec3f.h"

void	vec3f_set(t_vec3f *instance, float x, float y, float z)
{
  instance->x = x;
  instance->y = y;
  instance->z = z;
}

t_vec3f   *vec3f_new (float x, float y, float z)
{
  t_vec3f		*instance;

  instance = malloc(sizeof(t_vec3f));
  vec3f_set(instance, x, y, z);
  return (instance);
}

t_vec3f   *vec3f_new_unit (float x)
{
  return (vec3f_new(x, x, x));
}

float	length2(t_vec3f *a)
{
  return (a->x * a->x + a->y * a->y + a->z * a->z);
}

float	length(t_vec3f *a)
{
  return (sqrt(length2(a)));
}

t_vec3f	*vec3f_normalize(t_vec3f *a)
{
  float	nor2;

  nor2 = length2(a);
  if (nor2 > 0)
    {
      float invNor = 1 / sqrt(nor2);
      a->x *= invNor;
      a->y *= invNor;
      a->z *= invNor;
    }
  return (a);
}

t_vec3f	*vec3f_mul_unit (t_vec3f *a, float f)
{
  return (vec3f_new(a->x * f, a->y * f, a->z * f));
}
    
t_vec3f	*vec3f_mul (t_vec3f *a, t_vec3f *b)
{
  return (vec3f_new(a->x * b->x, a->y * b->y, a->z * b->z));
}

float	vec3f_dot (t_vec3f *a, t_vec3f *b)
{
  return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vec3f	*vec3f_sub (t_vec3f *a, t_vec3f *b)
{
  return (vec3f_new(a->x - b->x, a->y - b->y, a->z - b->z));
}

t_vec3f	*vec3f_add (t_vec3f *a, t_vec3f *b)
{
  return (vec3f_new(a->x + b->x, a->y + b->y, a->z + b->z));
}

t_vec3f	*vec3f_negate (t_vec3f *a)
{
  a->x = -a->x;
  a->y = -a->y;
  a->z = -a->z;
  return (a);
}

void	vec3f_print (t_vec3f *a)
{
  printf("vecteur : x:%f y:%f z:%f\n", a->x, a->y, a->z);
  fflush(stdout);
}
