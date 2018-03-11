#include "rtv1.h"

float mix(const float a, const float b, const float mix)
{
  return (b * mix + a * (1 - mix));
}

t_sphere	*search_intersection(t_sphere **spheres, t_vec3f *rayorig,
				     t_vec3f *raydir, float *tnear)
{
  t_sphere *sphere = NULL;
  float t0 = INFINITY, t1 = INFINITY;
  
  while(*spheres)
    {
      if (sphere_intersect(*spheres, rayorig, raydir, &t0, &t1))
	{
	  if (t0 < 0)
	    t0 = t1;
	  if (t0 < *tnear) {
	    *tnear = t0;
	    sphere = *spheres;
	  }
        }
      ++spheres;
    }
  return (sphere);
}

t_vec3f		*f(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit,
		   float bias, t_sphere *sphere)
{
  int 		i = 0;
  t_vec3f	*surface_color = vec3f_new_unit(0);
  
  while(spheres[i])
    {
      if (spheres[i]->emission_color->x > 0)
	{
	  t_vec3f *transmission = vec3f_new_unit(1);
	  t_vec3f *light_direction = vec3f_sub(spheres[i]->center, phit);
	  vec3f_normalize(light_direction);
	  int j = 0;
	  while (spheres[j])
	    {
	      if (i != j)
		{
		  float t0, t1;
		  if (sphere_intersect(spheres[j],
				       vec3f_add(phit, vec3f_mul_unit(nhit, bias)),
				       light_direction, &t0, &t1))
		    {
		      transmission = vec3f_new_unit(0);
		      break;
		    }
		}
	      ++j;
	    }
	  surface_color = vec3f_add(surface_color,
				    vec3f_mul(sphere->surface_color,
					      vec3f_mul(vec3f_mul_unit(transmission,
								       fmax(0.0, vec3f_dot(nhit, light_direction))),
							spheres[i]->emission_color)
					      ));
	}
      ++i;
    }
  return (vec3f_add(surface_color, sphere->emission_color));
}

t_vec3f		*g(t_sphere **spheres, t_vec3f *phit, t_vec3f *nhit,
		   float bias, t_sphere *sphere, t_vec3f *raydir, float depth)
{
  int inside = 0;
  if (vec3f_dot(raydir, nhit) > 0)
    {
      vec3f_negate(nhit);
      inside = 1;
    }
  t_vec3f *surface_color = vec3f_new_unit(0);
  float facingratio = vec3f_dot(vec3f_negate(raydir), nhit);
  float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
  t_vec3f *refldir = vec3f_sub(raydir, vec3f_mul_unit(nhit, 2 * vec3f_dot(raydir, nhit)));
  vec3f_normalize(refldir);
  t_vec3f *reflection = trace(vec3f_add(phit, vec3f_mul_unit(nhit, bias)),
			      refldir, spheres, depth + 1);
  t_vec3f *refraction = vec3f_new_unit(0);
  if (sphere->transparency)
    {
      float ior = 1.1, eta = (inside) ? ior : 1 / ior;
      float cosi = - vec3f_dot(nhit, raydir);
      float k = 1 - eta * eta * (1 - cosi * cosi);
      t_vec3f *refrdir = vec3f_add(vec3f_mul_unit(raydir, eta), vec3f_mul_unit(nhit, eta *  cosi - sqrt(k)));
      vec3f_normalize(refrdir);
      refraction = trace(vec3f_sub(phit, vec3f_mul_unit(nhit, bias)), refrdir, spheres, depth + 1);
    }
  surface_color = vec3f_mul(vec3f_add(vec3f_mul_unit(reflection, fresneleffect),
				      vec3f_mul_unit(refraction, 1 - fresneleffect * sphere->transparency)),
			    sphere->surface_color);
}

t_vec3f		*trace(t_vec3f *rayorig, t_vec3f *raydir,
		       t_sphere **spheres, int depth)
{
  float tnear = INFINITY;
  t_sphere *sphere = NULL;
  sphere = search_intersection(spheres, rayorig, raydir, &tnear);
  if (!sphere)
    return (vec3f_new(2, 0.1, 0.5));
  t_vec3f *surface_color = vec3f_new_unit(0);
  t_vec3f *phit = vec3f_add(rayorig, vec3f_mul_unit(raydir, tnear));
  t_vec3f *nhit = vec3f_sub(phit, sphere->center);
  vec3f_normalize(nhit);
  float bias = 1e-4;
  if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH)
    return(g(spheres, phit, nhit, bias, sphere, raydir, depth));
  else
   return(f(spheres, phit, nhit, bias, sphere));
}
