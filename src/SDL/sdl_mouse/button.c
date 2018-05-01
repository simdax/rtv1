/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:19:30 by acourtin          #+#    #+#             */
/*   Updated: 2018/05/01 17:10:39 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_mouse.h"

static void		handle_events(t_button *self, SDL_Event *e, int inside)
{
	!inside ? self->current_sprite = BUTTON_SPRITE_MOUSE_OUT : 0;
	if (inside)
	{
		if (e->type == SDL_MOUSEMOTION)
		{
			self->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
			self->t->dstrect.y = self->t->tmp + 2;
		}
		else if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			self->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
		//	self->func ? self->func(self->param) : ft_putendl("No function...");
			self->func ? self->trigger = 1 : ft_putendl("No function...");
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
			self->current_sprite = BUTTON_SPRITE_MOUSE_UP;
	}
}

void			button_handle_event(t_button *self, SDL_Event *e)
{
	int x;
	int y;
	int inside;

	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN \
			|| e->type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		self->t->dstrect.y = self->t->tmp;
		inside = x < self->position.x ? 0 : 1;
		x > self->position.x + self->width ? inside = 0 : 0;
		y < self->position.y ? inside = 0 : 0;
		y > self->position.y + self->height ? inside = 0 : 0;
		handle_events(self, e, inside);
	}
}

void			button_render(t_button *self, SDL_Renderer *renderer)
{
	t_txt_renderer t;

	t.x = self->position.x;
	t.y = self->position.y;
	t.clip = &self->clips[self->current_sprite];
	t.angle = 0.0;
	t.center = NULL;
	self->texture->texture_render(self->texture, &t, \
				SDL_FLIP_NONE, renderer);
}

void			button_free(t_button *self)
{
	if (self->texture->texture)
		self->texture->texture_free(self->texture);
	free(self);
}

t_button		*button_new(int x, int y, int width, int height)
{
	t_button *button;

	button = NULL;
	if (!(button = ft_memalloc(sizeof(*button))))
		return (NULL);
	button->position.x = x;
	button->position.y = y;
	button->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
	button->button_handle_event = button_handle_event;
	button->button_render = button_render;
	button->button_free = button_free;
	button->width = width;
	button->height = height;
	return (button);
}
