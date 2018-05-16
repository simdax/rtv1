typedef struct	s_vec3f {
	double x;
	double y;
	double z;
}				t_vec3f;

__kernel void length2(__global t_vec3f *a, __global double *d)
{
	*d = a->x * a->x + a->y * a->y + a->z * a->z;
}

