/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 13:55:55 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/24 18:26:32 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include "libft.h"
# include <math.h>
# include <float.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define W_LENGHT 1000
# define W_WIDTH 1000
# define EPSILON 0.0001

typedef struct	s_vecteur
{
	double		x;
	double		y;
	double		z;
}				t_vecteur;

typedef struct	s_record
{
	double		t;
	t_vecteur	p;
	t_vecteur	normal;
	t_vecteur	color;
	int			hit_anything;
	double		ks;
	double		kt;
	int			inside;
	int			index;
	int			f;
}				t_record;

typedef struct	s_ray2
{
	t_vecteur	ori;
	t_vecteur	dir;
}				t_ray2;

typedef struct	s_sphere2
{
	t_vecteur	center;
	double		radius;
	t_vecteur	c;
}				t_sphere2;

typedef struct	s_cylindre
{
	t_vecteur	base;
	t_vecteur	dir;
	double		radius;
	t_vecteur	color;
}				t_cylindre;

typedef struct	s_cone2
{
	t_vecteur	apex;
	t_vecteur	dir;
	double		angle;
	t_vecteur	color;
}				t_cone2;

typedef struct	s_plan
{
	t_vecteur	point;
	t_vecteur	vdir;
	t_vecteur	color;
	double		size;
}				t_plan;

typedef struct	s_fcylindre
{
	t_vecteur	base;
	t_vecteur	dir;
	double		radius;
	t_vecteur	color;
	double		size;
	t_plan		*plan1;
	t_plan		*plan2;
}				t_fcylindre;

typedef struct	s_fcone
{
	t_vecteur	apex;
	t_vecteur	dir;
	double		angle;
	t_vecteur	color;
	double		mid;
	double		size;
	t_plan		*plan1;
	t_plan		*plan2;
}				t_fcone;

typedef struct	s_formlist
{
	void		*form;
	int			type;
	int			size;
	t_vecteur	color;
	double		ks;
	double		kt;
	int			index;
}				t_formlist;

typedef struct	s_scene
{
	t_formlist	*list;
	t_vecteur	*light;
	t_vecteur	camorigin;
	t_vecteur	camdir;
	int			n_light;
	int			n_obj;
	int			i;
	int			k;
}				t_scene;

# include "rtv1.h"

t_vecteur		v_add(t_vecteur v1, t_vecteur v2);
t_vecteur		v_less(t_vecteur v1, t_vecteur v2);
t_vecteur		v_cross(t_vecteur v1, t_vecteur v2);
double			v_dot(t_vecteur v1, t_vecteur v2);
double			v_norm(t_vecteur v);
t_vecteur		v_mult(t_vecteur v1, double i);
int				v_equal(t_vecteur v1, t_vecteur v2);
t_vecteur		v_div(t_vecteur v1, double i);
t_vecteur		v_set(double x, double y, double z);
t_vecteur		v_normalize(t_vecteur v);
int				my_key_funct(int keycode);
int				set_sphere(t_scene *scene, char **tab);
void			set_min_max(double min, double max, double *min_max);
int				hit_sphere(t_sphere2 *sphere, t_ray2 *ray,
		double *min_max, t_record *rec);
int				hit_cone(t_cone2 *cone, t_ray2 *ray,
		double *min_max, t_record *rec);
int				hit_cylindre(t_cylindre *cyl, t_ray2 *ray,
		double *min_max, t_record *rec);
int				hit_plan(t_plan *plan, t_ray2 *ray,
		double *min_max, t_record *rec);
int				hit_qqch(t_formlist *list, t_ray2 *ray,
		double *min_max, t_record *rec);
t_formlist		*set_list(void);
void			sphere_rec(t_ray2 *ray, double t, t_sphere2 *s, t_record *rec);
void			cyl_rec(t_ray2 *ray, double t, t_cylindre *cyl, t_record *rec);
void			cone_rec(t_ray2 *ray, double t, t_cone2 *cone, t_record *rec);
double			*cone_tab(t_cone2 *cone, t_ray2 *ray);
void			ret_inter(t_formlist list, double *min_max,
		t_record *rec, int *hit);
t_vecteur		libe(void **r, double *min_max, t_vecteur vr);
t_vecteur		r_color(t_ray2 *ray, t_scene scene, int depht);
void			printexit(void);
void			tab_free(char **tab, char *line);
int				set_plan(t_scene *scene, char **tab);
int				set_cylindre(t_scene *scene, char **tab);
int				set_cone(t_scene *scene, char **tab);
int				set_light(t_scene *scene, char **tab);
int				set_cam(t_scene *scene, char **tab);
void			ft_parseur(char **av, t_scene *scene);
void			shadow_ret_inter(t_formlist list, double *min_max, \
		t_record *rec, int *hit);
int				shadow_hit_qqch(t_formlist *list, t_ray2 *ray, \
		double *min_max, t_record *rec);
int				hit_fcylindre(t_fcylindre *fcyl, t_ray2 *ray, \
		double *min_max, t_record *rec);
int				hit_fcone(t_fcone *fcone, t_ray2 *ray, double *min_max, \
		t_record *rec);
void			ft_convert(t_obj **obj, t_scene *scene);
void			ft_raytrace(t_scene *scene, t_vec3f *color, t_vec3f ori, \
		t_vec3f dir);
void			fcylindre_def(t_obj *obj, t_scene *scene);
void			def_fcone(t_obj *obj, t_scene *scene);
void			free_scene(t_scene *scene);
#endif
