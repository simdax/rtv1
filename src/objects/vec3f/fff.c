#include "vec3f.h"

void	vec3f_cpy (t_vec3f *a, t_vec3f *b)
{
  vec3f_set(a, b->x, b->y, b->z);
}

void	vec3f_mul_unit2 (t_vec3f *a, float f)
{
  vec3f_set(a, a->x * f, a->y * f, a->z * f);
}
    
void	vec3f_mul2 (t_vec3f *a, t_vec3f *b)
{
  vec3f_set(a, a->x * b->x, a->y * b->y, a->z * b->z);
}

void	vec3f_add2 (t_vec3f *a, t_vec3f *b)
{
  vec3f_set(a, a->x + b->x, a->y + b->y, a->z + b->z);
}

void	vec3f_add_unit2 (t_vec3f *a, float b)
{
  vec3f_set(a, a->x + b, a->y + b, a->z + b);
}

void	vec3f_sub2 (t_vec3f *a, t_vec3f *b)
{
  vec3f_set(a, a->x - b->x, a->y - b->y, a->z - b->z);
}

void	vec3f_normalize2(t_vec3f *a)
{
  vec3f_mul_unit2(a, 1 / length(a));
}
