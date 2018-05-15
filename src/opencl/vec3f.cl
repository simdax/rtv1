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
