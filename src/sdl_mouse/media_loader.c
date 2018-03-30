#include <stdarg.h>
#include "sdl_mouse.h"

// Une fonction pour charger automatiquement des images reactives

// args: nb
// les functions a arguments variables en C doivent indiquer
// le nb d'argument en debut de fonction

// args: path
// le chemin ou trouver le fichier des images. On doit indiquer
// une 'spritesheet' c'est a dire une image avec plusieurs images
// pour pouvoir simuler differents 'etats' (l'image change selon si
// la souris est dessus ou non, si elle clique etc.)

// args: nb_states et clips
// il faut donc indiquer le nb d'etats possibles, et la taille veritable
// de l'image (si l'image fait en vrai 100*100, la spritesheet fera 100* nb_states * 100)

// le reste des arguments indique le nb de buttons similaires a creer, et leur position
// x y

t_button	**media_loader(int nb, char *path,
			       int nb_states, SDL_Rect size, ...)
{
  va_list	ap;
  t_button	**ptr;
  int		i;
  
  i = -1;
  ptr = (t_button**)malloc(sizeof(t_button*) * nb + 1);
  va_start(ap, size);
  while (++i < nb)
    {
      ptr[i] = button_new(va_arg(ap, int), va_arg(ap, int));
      int j = -1;
      while (++j < nb_states)
	{
	  ptr[i]->clips[j] = size;
	  ptr[i]->clips[j].y = size.y * j;
	}
    }
  ptr[i] = 0;
  va_end(ap);
  return (ptr);
}
