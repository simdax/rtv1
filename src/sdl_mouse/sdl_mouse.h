/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:48:35 by acourtin          #+#    #+#             */
/*   Updated: 2018/03/28 18:17:00 by acourtin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_MOUSE_H
# define SDL_MOUSE_H

# include <SDL.h>
# include <SDL_image.h>

# define S_WTH 640
# define S_HGT 480
# define B_WTH 300
# define B_HGT 200

typedef enum	e_btnsprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
}				t_btnsprite;

typedef struct	s_txt_renderer
{
	int			x;
	int			y;
	SDL_Rect	*clip;
	double		angle;
	SDL_Point	*center;
}				t_txt_renderer;

typedef struct	s_texture
{
	int			width;
	int			height;
	SDL_Texture	*texture;
	int			(*texture_load_from_file)(struct s_texture *t, \
					const char *path, SDL_Renderer *renderer);
	void		(*texture_set_color)(struct s_texture *t, int red, int green, \
					int blue);
	void		(*texture_free)(struct s_texture *t);
	void		(*texture_set_blend_mode)(struct s_texture *t, \
					SDL_BlendMode blending);
	void		(*texture_set_alpha)(struct s_texture *t, int alpha);
	void		(*texture_render)(struct s_texture *self, \
		struct		s_txt_renderer *t, SDL_RendererFlip flip, \
		SDL_Renderer *renderer);
}				t_texture;

typedef struct	s_button
{
	SDL_Point	position;
	t_btnsprite	current_sprite;
	void		(*button_set_pos)(struct s_button *self, int x, int y);
	void		(*button_handle_event)(struct s_button *self, SDL_Event *e);
	void		(*button_render)(struct s_button *self, \
		t_texture	*button_texture, SDL_Rect *sprite_clips, \
		SDL_Renderer *renderer);
}				t_button;

typedef struct	s_main
{
	SDL_Window	*window;
	SDL_Rect	sprite_clip[4];
	SDL_Event	e;
	t_texture	*texture_button;
	t_button	*buttons[4];
	int			quit;
	int			i;
}				t_main;

int				texture_load_from_file(t_texture *self, const char *path, \
					SDL_Renderer *renderer);
void			texture_free(t_texture *self);
void			texture_render(t_texture *self, t_txt_renderer *t, \
		SDL_RendererFlip flip, SDL_Renderer *renderer);
void			texture_set_color(t_texture *self, int r, int g, int b);
void			texture_set_blend_mode(t_texture *self, SDL_BlendMode blending);
void			texture_set_alpha(t_texture *self, int alpha);
void			button_set_position(t_button *self, int x, int y);
void			button_handle_event(t_button *self, SDL_Event *e);
void			button_render(t_button *self, t_texture *button_texture, \
					SDL_Rect *sprite_clips, SDL_Renderer *renderer);
t_texture		*texture_new(void);
t_button		*button_new(void);

#endif
