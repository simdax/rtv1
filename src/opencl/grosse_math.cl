
typedef struct	s_vec3f {
	double x;
	double y;
	double z;
}				t_vec3f;

__kernel void resolve_quadratic(__global t_vec3f *equation, __global double *solution)
{
	double	det;
	double	t1;
	double	t2;

	det = equation->y * equation->y - 4 * equation->x * equation->z;
	if (det < 0)
		*solution = -1;
	det = sqrt(det);
	t1 = (-equation->y + det) / (2 * equation->x);
	t2 = (-equation->y - det) / (2 * equation->x);
	if (t1 < 0 && t2 < 0)
		*solution = -1;
	else if (t2 > 0 && t2 < t1)
		*solution = t2;
	else
		*solution = t1;
	*solution = det;
}
