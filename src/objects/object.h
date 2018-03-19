#ifndef OBJECT_H
# define OBJECT_H

# include "vec3f/vec3f.h"

typedef struct	s_hit{
  float		*tnear;
  t_vec3f	*rayorig;
  t_vec3f	*raydir;
  t_vec3f	*nhit;
  t_vec3f	*phit;
  t_vec3f	*color;
  int		inside;
  float		transmission;
  t_vec3f	*refldir;
  t_vec3f	*refraction;
  float		facingratio;
}		t_hit;

# include "libft.h"
# include "sphere.h"

typedef struct	s_obj{
  char		*tag;
  union	u_type{
    t_sphere	*sphere;
  }     	obj;
  float		transparency;
  float		reflection;
  t_vec3f	surface_color;
  t_vec3f       emission_color;
}		t_obj;

typedef struct	s_plane
{
    float	d;	// solution to dot(n,p)+d=0
    t_vec3f	n;		// normal
}		t_plane;

typedef struct	s_cone
{
  float		angle;
  float		angle2;
  float		height;
  t_vec3f	tip_position;		
  t_vec3f	axis;	        
}		t_cone;

t_obj		object_new(char *type, char *parent);
void		del_object(void *c, size_t size);
void		object_set(t_obj *obj, char *type, char *prop, void *val);
void		object_print(t_obj *obj);
int		object_intersect(t_obj *obj,
				 t_vec3f *rayorig, t_vec3f *raydir,
				 float *t0, float *t1);
void		object_normale(t_obj *obj, t_hit *hit);
t_obj		**configure(char *config_file);

#endif
