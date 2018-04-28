/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:19:30 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/28 16:27:17 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_mouse.h"

static void		handle_events(t_button *self, SDL_Event *e)
{
	int x;
	int y;
	int inside;

	inside = 1;
	SDL_GetMouseState(&x, &y);
	x < self->position.x ? inside = 0 : 0;
	x > self->position.x + self->width ? inside = 0 : 0;
	y < self->position.y ? inside = 0 : 0;
	y > self->position.y + self->height ? inside = 0 : 0;
	if (!inside)
		self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
	else
	{
		if (e->type == SDL_MOUSEMOTION)
			self->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
		else if (e->type == SDL_MOUSEBUTTONDOWN)
		{
			self->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
			self->func(self->param);
		}
		else if (e->type == SDL_MOUSEBUTTONUP)
			self->current_sprite = BUTTON_SPRITE_MOUSE_UP;
	}
}

void			button_handle_event(t_button *self, SDL_Event *e)
{
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN \
			|| e->type == SDL_MOUSEBUTTONUP)
		handle_events(self, e);
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

	button = (t_button*)malloc(sizeof(*button));
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
