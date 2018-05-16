typedef struct	s_vec3f {
	double x;
	double y;
	double z;
}				t_vec3f;

__kernel void add_vec3f(__global t_vec3f *v1, __global t_vec3f *v2, __global t_vec3f *vo)
{
	vo->x = v1->x + v2->x;
	vo->y = v1->y + v2->y;
	vo->z = v1->z + v2->x;
}

__kernel void sub_vec3f(__global t_vec3f *v1, __global t_vec3f *v2, __global t_vec3f *vo)
{
	vo->x = v1->x - v2->x;
	vo->y = v1->y - v2->y;
	vo->z = v1->z - v2->x;
}

__kernel void vec3f_mul_unit(__global t_vec3f *v1, __global double *d, __global t_vec3f *vo)
{
	vo->x = v1->x * *d;
	vo->y = v1->y * *d;
	vo->z = v1->z * *d;
}

__kernel void length2(__global t_vec3f *a, __global double *d)
{
	*d = a->x * a->x + a->y * a->y + a->z * a->z;
}

__kernel void length3(__global t_vec3f *a, __global double *d)
{
	length2(a, d);
	*d = sqrt(*d);
}

__kernel void vec3f_dot(__global t_vec3f *a, __global t_vec3f *b, __global double *o)
{
	*o = a->x * b->x + a->y * b->y + a->z * b->z;
}

__kernel void vec3f_negate(__global t_vec3f *a, __global t_vec3f *b)
{
	b->x = -a->x;
	b->y = -a->y;
	b->z = -a->z;
}

__kernel void vec3f_normalize(__global t_vec3f *a, __global t_vec3f *b)
{
	double length;

	length = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
	b->x = a->x * 1 / length;
	b->y = a->y * 1 / length;
	b->z = a->z * 1 / length;
}
