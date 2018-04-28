/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_mouse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:48:35 by acourtin          #+#    #+#             */
/*   Updated: 2018/04/28 15:34:48 by alerandy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_MOUSE_H
# define SDL_MOUSE_H

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>

# define S_WTH 1200
# define S_HGT 800
# define B_WTH 175
# define B_HGT 36

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
	SDL_Rect	clips[4];
	t_texture	*texture;
	void		(*button_handle_event)(struct s_button *self, SDL_Event *e);
	void		(*button_render)(struct s_button *self, SDL_Renderer *renderer);
	void		(*button_free)(struct s_button *self);
	int			width;
	int			height;
	void		(*func)(void *param);
	void		*param;
}				t_button;

typedef struct	s_interface
{
	SDL_Window	*window;
	SDL_Event	e;
	t_texture	*texture_button;
	t_button	**buttons;
	t_texture	**textures;
	int			quit;
	int			i;
	void		(*loop)(struct s_interface *self, SDL_Renderer *renderer,
					SDL_Event *e);
	void		(*free)(struct s_interface *self);
}				t_interface;

int				texture_load_from_file(t_texture *self, const char *path, \
					SDL_Renderer *renderer);
void			texture_free(t_texture *self);
void			texture_render(t_texture *self, t_txt_renderer *t, \
		SDL_RendererFlip flip, SDL_Renderer *renderer);
void			texture_set_color(t_texture *self, int r, int g, int b);
void			texture_set_blend_mode(t_texture *self, SDL_BlendMode blending);
void			texture_set_alpha(t_texture *self, int alpha);
void			button_handle_event(t_button *self, SDL_Event *e);
void			button_render(t_button *self, SDL_Renderer *renderer);
t_texture		*texture_new(void);
t_button		*button_new(int x, int y, int width, int height);
void			button_free(t_button *self);
t_button		**buttons_loader(int nb, t_texture *txt,
int				nb_states, SDL_Rect size, ...);
t_texture		**textures_loader(int nb, SDL_Renderer *renderer, ...);
void			free_buttons(t_interface *m);

#endif
