#include "rtv1.h"
#include "gnl/get_next_line.h"

typedef struct		s_obj {
  char			*name;
  t_vec3f		position;
  t_vec3f		color;
  t_sphere_infos	infos;
}			t_obj;

void	free_obj(t_obj *obj)
{
  free(obj->infos);
  free(obj->color);
  free(obj->position);
  free(obj->name);
}

t_vec3f	parse_par(char *buf)
{
  if (buf[0] == '(')
    {
      
    }
}

int	parse2(char *buf)
{
  char			*name;
  t_vec3f		color;
  t_vec3f		position;
  t_sphere_infos	infos;
  char			**cpy;

  cpy = ft_strsplit(buf, ' ');
  if (ft_strsplit_len(cpy) == 4)
    {
      name = cpy[0];
      position = parse_par(cpy[1]);
      color = parse_par(cpy[2]);
      infos = parse_par(cpy[3]);
      return (1);
    }
  return (0);
}

void	parse(char *path)
{
  int fd = open(path, O_RDONLY);
  char		*buf;
  
  while(get_next_line(fd, buf))
    {
      parse2(buf);
    }
}
