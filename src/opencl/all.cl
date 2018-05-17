typedef struct	s_vec3f {
	double x;
	double y;
	double z;
}		t_vec3f;

typedef struct	s_33mat{
	t_vec3f	up;
	t_vec3f	right;
	t_vec3f	forward;
	t_vec3f	transpose;
}		t_33mat;

__kernel void vec3f_add(__global t_vec3f *v1, __global t_vec3f *v2, __global t_vec3f *vo)
{
	vo->x = v1->x + v2->x;
	vo->y = v1->y + v2->y;
	vo->z = v1->z + v2->x;
}

__kernel void vec3f_sub(__global t_vec3f *v1, __global t_vec3f *v2, __global t_vec3f *vo)
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

__kernel void vec3f_length2(__global t_vec3f *a, __global double *d)
{
	*d = a->x * a->x + a->y * a->y + a->z * a->z;
}

__kernel void vec3f_length3(__global t_vec3f *a, __global double *d)
{
	t_vec3f	length2(a, d);
	*d = sqrt(*d);
}

__kernel void vec3f_cpy(__global t_vec3f *a, __global t_vec3f *b)
{
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
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

__kernel void vec3f_normalize2(__global t_vec3f *a, __global t_vec3f *b)
{
	unsigned int i = get_global_id(0);
	double length;

	vec3f_normalize(&a[i], &b[i]);
}
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
typedef struct	s_hit{
	double		tnear;
	t_vec3f		rayorig;
	t_vec3f		raydir;
	int		obj_index;
	t_vec3f		nhit;
	t_vec3f		phit;
	t_vec3f		color;
	t_vec3f		distance;
	int		inside;
	double		transmission;
	t_vec3f		refldir;
	t_vec3f		refraction;
	double		facingratio;
	t_vec3f		cp;
	double		max;
}		t_ray;

typedef struct	s_sphere {
	t_vec3f		center;
	double		radius;
	double		radius2;
}		t_sphere;

__kernel void sphere_intersect(__global t_sphere *sphere, __global t_ray *hit, __global double *res)
{
	double		thc;
	double		tca;
	double		d2;
	t_vec3f		l;
	
        l.x = sphere->center.x - hit->rayorig.x;
	l.y = sphere->center.x - hit->rayorig.y;
	l.z = sphere->center.x - hit->rayorig.z;
	tca = l.x * hit->rayorig.x + l.y * hit->rayorig.y + l.z * hit->rayorig.z;
	if (tca < 0)
	  *res = -1;
	d2 = l.x * l.x + l.y * l.y + l.z * l.z - tca * tca;
	if (d2 > sphere->radius2)
	  *res = -1;
	thc = sqrt(sphere->radius2 - tca);
	if ((*res = tca - thc) < 0)
	  *res = tca + thc;
	*res = -1;
}

__kernel void	sphere_normale(t_sphere *sphere, t_ray *hit)
{
	vec3f_sub(&hit->nhit, &(sphere->center));
}
