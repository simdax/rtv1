int		plane_intersect(t_sphere *sphere,
				t_vec3f *orig, t_vec3f *dir,
				float *t0, float *t1)
{
  (void)t1;
  t_vec3f n = (t_vec3f){-0.5, -2, -0.5};
  vec3f_normalize(&n);
  float denom = vec3f_dot(&n, dir);
  if (denom > 1e-6) {
    //    printf("fdsf");
    t_vec3f p0l0 = sphere->center;
    vec3f_sub(&p0l0, orig);
    *t0 = vec3f_dot(&p0l0, &n) / denom;
    return (*t0 >= 0);
  }
  return (0);
}
