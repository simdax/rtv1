#ifndef OBJECT_H
# define OBJECT_H

# include "vec3f/vec3f.h"

typedef struct	s_hit{
  float		tnear;
  t_vec3f	*rayorig;
  t_vec3f	*raydir;
  int		obj_index;
  t_vec3f	*nhit;
  t_vec3f	*phit;
  t_vec3f	*color;
  int		inside;
  float		transmission;
  t_vec3f	*refldir;
  t_vec3f	*refraction;
  float		facingratio;
  t_vec3f	*cp;
}		t_hit;

# include "sphere.h"
# include "cone.h"
# include "cylinder.h"
# include "plane.h"

typedef struct	s_obj{
  char		*tag;
  union		u_type{
    t_sphere	*sphere;
    t_cone	*cone;
    t_plane	*plane;
    t_cylinder	*cylinder;
  }     	obj;
  float		transparency;
  float		reflection;
  t_vec3f	surface_color;
  t_vec3f       emission_color;
  t_vec3f       position;
}		t_obj;

# include "libft.h"

t_obj		object_new(char *type, char *parent);
void		del_object(void *c, size_t size);
void		object_set(t_obj *obj, char *type, char *prop, void *val);
void		object_print(t_obj *obj);
int		object_intersect(t_obj *obj, t_hit *hit,
				 float *t0);
void		object_normale(t_obj *obj, t_hit *hit);
t_obj		**configure(char *config_file);

#endif
