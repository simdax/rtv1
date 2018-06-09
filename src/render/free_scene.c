/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:07:01 by cbesse            #+#    #+#             */
/*   Updated: 2018/05/23 16:07:02 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rt.h"

void free_fcyl(t_fcylindre *fcyl)
{
  ft_memdel((void *)&fcyl->plan1);
  ft_memdel((void *)&fcyl->plan2);
}

void free_fcone(t_fcone *fcyl)
{
  ft_memdel((void *)&fcyl->plan1);
  ft_memdel((void *)&fcyl->plan2);
}

void free_scene(t_scene *scene)
{
  int i;

  i = -1;
  while(++i < scene->n_obj)
  {
    if(scene->list[i].type == 5)
      free_fcyl(scene->list[i].form);
    if(scene->list[i].type == 6)
      free_fcone(scene->list[i].form);
    ft_memdel((void **)&scene->list[i].form);
    ft_memdel((void *)&scene->list[i]);
  }
  ft_memdel((void *)&scene->list);
  ft_memdel((void *)&scene->light);
  ft_memdel((void *)&scene);
}
