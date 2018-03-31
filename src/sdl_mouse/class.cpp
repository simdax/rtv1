#include <SDL.h>
#include <SDL_image.h>

typedef struct	s_texture {
  int		width;
  int		height;
  SDL_Texture	*texture;
  int		(*texture_load_from_file)(struct s_texture *t, char *path, SDL_Renderer *gRenderer);
  void		(*texture_set_color)(struct s_texture *t, int red, int green, int blue);
  void		(*texture_free)(struct s_texture *t);
  void		(*texture_set_blend_mode)(struct s_texture *t, SDL_BlendMode blending);
  void		(*texture_set_alpha)(struct s_texture *t, int alpha);
  void		(*texture_render)(struct s_texture *t, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip, SDL_Renderer *gRenderer);
}		t_texture;

int		texture_load_from_file(t_texture *self, char *path, SDL_Renderer *gRenderer)
{
  SDL_Texture	*new_texture;
  SDL_Surface	*loaded_surface;

  self->texture_free(self);
  loaded_surface = IMG_Load(path);
  if (!loaded_surface)
    printf("pb de texture: %s\n", IMG_GetError());
  else
    {
      SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xff, 0xFF));
      new_texture = SDL_CreateTextureFromSurface(gRenderer, loaded_surface);
      if (!new_texture)
	printf("pb de surface!, %s\n", SDL_GetError());
      else
	{
	  self->width = loaded_surface->w;
	  self->height = loaded_surface->h;
	}
      SDL_FreeSurface(loaded_surface);       
    }
  self->texture = new_texture;
  return (new_texture != NULL);
}

void		texture_free(t_texture *self)
{
  if (self->texture)
    {
      SDL_DestroyTexture(self->texture);
      self->texture = 0;
    }
  free(self);	
}

void		texture_render(t_texture *self, int x, int y, SDL_Rect *clip,
			       double angle, SDL_Point *center, SDL_RendererFlip flip,
			       SDL_Renderer *gRenderer)
{
  //Set rendering space and render to screen
  SDL_Rect renderQuad;

  renderQuad = (SDL_Rect){ x, y, self->width, self->height };
  //Set clip rendering dimensions
  if( clip != NULL )
    {
      renderQuad.w = clip->w;
      renderQuad.h = clip->h;
    }
  //Render to screen
  SDL_RenderCopyEx( gRenderer, self->texture, clip, &renderQuad, angle, center, flip );
}

void		texture_set_color(t_texture *self, int r, int g, int b)
{
  SDL_SetTextureColorMod(self->texture, r, g, b);
}

void		texture_set_blend_mode(t_texture *self, SDL_BlendMode blending)
{
  SDL_SetTextureBlendMode(self->texture, blending);
}

void		texture_set_alpha(t_texture *self, int alpha)
{
  SDL_SetTextureAlphaMod(self->texture, alpha);
}

t_texture	*texture_new()
{
  t_texture	*texture;

  texture = (t_texture*)malloc(sizeof(*texture));
  texture->width = 0;
  texture->height = 0;
  texture->texture = 0;
  texture->texture_free = texture_free;
  texture->texture_load_from_file = texture_load_from_file;
  texture->texture_set_color = texture_set_color;
  texture->texture_set_blend_mode = texture_set_blend_mode;
  texture->texture_set_alpha = texture_set_alpha;
  texture->texture_render = texture_render;
  return (texture);
}
