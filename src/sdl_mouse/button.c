/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:19:30 by acourtin          #+#    #+#             */
/*   Updated: 2018/03/28 18:07:44 by acourtin         ###   ########.fr       */
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
	if (x < self->position.x)
		inside = 0;
	else if (x > self->position.x + B_WTH)
		inside = 0;
	else if (y < self->position.y)
		inside = 0;
	else if (y > self->position.y + B_HGT)
		inside = 0;
	if (!inside)
		self->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
	else
	{
		if (e->type == SDL_MOUSEMOTION)
			self->current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
		else if (e->type == SDL_MOUSEBUTTONDOWN)
			self->current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
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

void			button_set_pos(t_button *self, int x, int y)
{
	self->position.x = x;
	self->position.y = y;
}

void			button_render(t_button *self, t_texture *button_texture, \
		SDL_Rect *sprite_clips, SDL_Renderer *renderer)
{
	t_txt_renderer t;

	t.x = self->position.x;
	t.y = self->position.y;
	t.clip = &sprite_clips[self->current_sprite];
	t.angle = 0.0;
	t.center = NULL;
	button_texture->texture_render(button_texture, &t, SDL_FLIP_NONE, renderer);
}

t_button		*button_new(int x, int y)
{
	t_button *button;

	button = (t_button*)malloc(sizeof(*button));
	button->position.x = x;
	button->position.y = y;
	button->current_sprite = BUTTON_SPRITE_MOUSE_OUT;
	button->button_set_pos = button_set_pos;
	button->button_handle_event = button_handle_event;
	button->button_render = button_render;
	return (button);
}
