#ifndef OBJECT_H
# define OBJECT_H

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

/* typedef struct	s_obj2{ */
/*   char		*tag; */
/*   float		transparency; */
/*   float		reflection; */
/*   t_vec3f	surface_color; */
/*   u_type{ */
/*     t_sphere	*sphere; */
/*   }     	obj; */
/* }		t_obj2; */

typedef struct	s_hit{
  float		tnear;
  t_vec3f	normale;
  t_vec3f	color;
}		t_hit;

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
t_sphere	**configure(char *config_file);

#endif
