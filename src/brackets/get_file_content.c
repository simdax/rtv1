#include "parser.h"

char     *get_file_content(char *path)
{
  int		fd;
  int		ret;
  char		buffer[65];
  t_array	*txt;
  char		*file_content;  

  txt = array_new(sizeof(char), 8);
  fd = open(path, O_RDONLY);
  if (fd)
    {
      while ((ret = read(fd, buffer, 64)) > 0)
	{
	  buffer[ret] = 0;
	  array_add(txt, buffer, ret);
	}
    }
  //  printf("%s", txt->mem);
  file_content = ft_strdup(txt->mem);
  array_free(txt);
  return (file_content);
}
