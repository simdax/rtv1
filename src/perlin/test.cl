__kernel void gradient_noise_d(__global const float3 *gradient_table, __global const double3 *p, __global float *res)
{
  double3 pos0 = floor(*p);
  float3 cube_pos0 = convert_float3(pos0);
  float3 cube_pos1 = cube_pos0 + 1;
  float3 t0 = convert_float3(*p - pos0);
  float3 t1 = t0 - 1;

  int x0 = cube_pos0.x;
  int y0 = cube_pos0.y;
  int z0 = cube_pos0.z;

  int x1 = cube_pos1.x;
  int y1 = cube_pos1.y;
  int z1 = cube_pos1.z;

  const int NOISE_HASH_X = 1213;
  const int NOISE_HASH_Y = 6203;
  const int NOISE_HASH_Z = 5237;
  const int NOISE_HASH_SEED = 1039;
  int ox0 = NOISE_HASH_X * x0 + NOISE_HASH_SEED;
  int oy0 = NOISE_HASH_Y * y0;
  int oz0 = NOISE_HASH_Z * z0;
  int ox1 = NOISE_HASH_X * x1 + NOISE_HASH_SEED;
  int oy1 = NOISE_HASH_Y * y1;
  int oz1 = NOISE_HASH_Z * z1;

  const int NOISE_HASH_SHIFT = 13;
  int index0 = ox0 + oy0 + oz0;
  int index1 = ox1 + oy0 + oz0;
  int index2 = ox0 + oy1 + oz0;
  int index3 = ox1 + oy1 + oz0;
  int index4 = ox0 + oy0 + oz1;
  int index5 = ox1 + oy0 + oz1;
  int index6 = ox0 + oy1 + oz1;
  int index7 = ox1 + oy1 + oz1;
  index0 ^= (index0 >> NOISE_HASH_SHIFT);
  index1 ^= (index1 >> NOISE_HASH_SHIFT);
  index2 ^= (index2 >> NOISE_HASH_SHIFT);
  index3 ^= (index3 >> NOISE_HASH_SHIFT);
  index4 ^= (index4 >> NOISE_HASH_SHIFT);
  index5 ^= (index5 >> NOISE_HASH_SHIFT);
  index6 ^= (index6 >> NOISE_HASH_SHIFT);
  index7 ^= (index7 >> NOISE_HASH_SHIFT);
  index0 &= 0xFF;
  index1 &= 0xFF;
  index2 &= 0xFF;
  index3 &= 0xFF;
  index4 &= 0xFF;
  index5 &= 0xFF;
  index6 &= 0xFF;
  index7 &= 0xFF;

  float3 grad0 = gradient_table[index0];
  float3 grad1 = gradient_table[index1];
  float3 grad2 = gradient_table[index2];
  float3 grad3 = gradient_table[index3];
  float3 grad4 = gradient_table[index4];
  float3 grad5 = gradient_table[index5];
  float3 grad6 = gradient_table[index6];
  float3 grad7 = gradient_table[index7];

/*   // Project permuted fractionals onto gradient vector */
  float4 g0246, g1357;
  g0246.x = dot(grad0, select(t0, t1, (int3){ 0, 0, 0}));
  g1357.x = dot(grad1, select(t0, t1, (int3){-1, 0, 0}));
  g0246.y = dot(grad2, select(t0, t1, (int3){ 0,-1, 0}));
  g1357.y = dot(grad3, select(t0, t1, (int3){-1,-1, 0}));
  g0246.z = dot(grad4, select(t0, t1, (int3){ 0, 0,-1}));
  g1357.z = dot(grad5, select(t0, t1, (int3){-1, 0,-1}));
  g0246.w = dot(grad6, select(t0, t1, (int3){ 0,-1,-1}));
  g1357.w = dot(grad7, select(t0, t1, (int3){-1,-1,-1}));

  float3 r = t0 * t0 * t0 * (t0 * (t0 * 6.0f - 15.0f) + 10.0f);
  float4 gx0123 = g0246 + r.x * (g1357 - g0246);
  float2 gy01 = gx0123.xz + r.y * (gx0123.yw - gx0123.xz);
  float gz = gy01.x + r.z * (gy01.y - gy01.x);

  *res = gz;
}

__kernel void io(__global double3 *o)
{
  *o = (double3){1., 2, 3};
}
