#include "object.h"
#include "vec3f.h"

void		object_texture(t_obj *obj, t_ray *hit)
{
  	t_vec3f	tmp;

	if (ft_strequ(obj->tag, "sphere"))
		sphere_texture(hit);
	/* else if (ft_strequ(obj->tag, "light")) */
	/* 	sphere_normale(obj->obj.sphere, hit); */
	/* else if (ft_strequ(obj->tag, "cone")) */
	/* 	cone_normale(obj->obj.cone, hit); */
	/* else if (ft_strequ(obj->tag, "plane")) */
	/* 	plane_normale(obj->obj.plane, hit); */
	/* else if (ft_strequ(obj->tag, "cylinder")) */
	/* 	cylinder_normale(obj->obj.cylinder, hit); */
}

static t_vec3f	get_pixel(int *img, int x, int y, int pitch)
{
	unsigned char	*rgb;
	t_vec3f			ret;

	unsigned pix = y * pitch + x * 3;
//printf("%f\n", x);
	rgb = (unsigned char*)(img + pix);
	ret.x = (double)rgb[0] / 255;
	ret.y = (double)rgb[1] / 255;
	ret.z = (double)rgb[2] / 255;
	return (ret);
}

t_vec3f		object_get_texture_pixel(double x, double y, t_obj *obj)
{
  	t_vec3f color;

//	if (y < 0.1)
	double w = obj->texture->w;
	double h = obj->texture->h;
	w /= 3;
	h /= 3;
	color = get_pixel(obj->texture->pixels, x * w, y * h, obj->texture->pitch);
	return (color);
}