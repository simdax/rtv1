__kernel void alexatan(__global double *av, __global double *ap)
{
	*ap = atan(*av) * atan(*av) * atan(*av) * atan(*av) * atan(*av);
}

__kernel void test42(__global int *i)
{
	*i = 42;
}
