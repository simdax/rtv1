#ifndef OBJECT_H
# define OBJECT_H

# include "libft.h"
# include "sphere.h"

typedef struct	s_obj{
  char		*tag;
  union	u_type{
    t_sphere	*sphere;
  }     	obj;
}		t_obj;

t_obj		object_new(char *type, char *parent);
void		del_object(void *c, size_t size);
void		object_set(t_obj *obj, char *type, char *prop, void *val);
void		object_print(t_obj *obj);
t_sphere	**configure(char *config_file);

#endif
