#include "stdio.h"
#include "libft.h"

void	print(char **buf, int flag, t_list **content)
{
  char const	*cpy;

  cpy = *buf;
  while (**buf && !(**buf == ')' ||
		    **buf == '('))
      *buf += 1;
  ft_lstadd(content, ft_lstnew(ft_strsub(cpy, 0, *buf - cpy), *buf - cpy + 1));
  //  printf("%s", content->content);
  //printf("%s -%d-\n", ft_strsub(cpy, 0, *buf - cpy), flag);
  *buf -= 1;
}

t_list	*brackets(char *buf, int flag)
{
  t_list	*inside = 0;

  inside = ft_lstnew(0, sizeof(t_list*));
  while (*buf)
    {
      if (*buf == '(')
	{
	  ft_lstadd(&inside, brackets(++buf, flag + 1)); 
	}
      else if (*buf == ')')
	return inside;
	//	return (brackets(++buf, flag - 1, &inside));
      else if (ft_issep(*buf))
	;
      else
	print(&buf, flag, &inside);
      ++buf;
    }
  //  return (flag);
  return (inside);
}

int	main(int argc, char **argv)
{
  t_list	*content;

  if (argc > 1)
    while(*(++argv))
        content = brackets(*argv, 0);
  return (0);
}
