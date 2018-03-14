#ifndef F_WRAPPER_H
# define F_WRAPPER_H

typedef union	u_func{
    char	**(*strsplit)(const char *txt, char c);
    void	*(*print)(const char *txt);
}		t_func;

typedef struct	s_fwrapper{
  t_func	func;
  char		c;
}		t_fwrapper;

#endif
