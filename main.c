#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <mlx.h>

#include "rt.h"

int		calc(int x, int y, t_point *eye, t_list *object_list)
{
  t_vector	v;
  double	tmp;
  double	k;
  int		color;

  v.x = 100;
  v.y = X / 2 - x;
  v.z = Y / 2 - y;
  k = -1;
  color = 0;
  while (object_list != NULL)
    {
      tmp = object_list->fct(&v, eye, object_list->obj);
      if (tmp > 0 && (k == -1 || tmp < k))
	{
	  k = tmp;
	  color = object_list->obj->color;
	}
      object_list = object_list->next;
    }
  return (color);
}

void	init(t_point *eye)
{
  eye->x = -300;
  eye->y = 0;
  eye->z = 100;
}

int	handle_key(int key, void *param)
{
  param = NULL;
  if (key == 65307)
    exit(0);
  return (0);
}

int	handle_expose(t_mlx *mlx)
{
  if (mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0) < 0)
    return (1);
  return (0);
}

int	check_display_env()
{
  char *display = getenv("DISPLAY");
  return (display && strlen(display) != 0);
}

int		main()
{
  t_mlx		mlx;
  t_point	eye;
  t_list	*object_list;

  if (!check_display_env())
    {
      fprintf(stderr, "DISPLAY not specified\n");
      return (1);
    }
  init(&eye);
  object_list = load_objects();
  if (object_list == NULL)
    {
      fprintf(stderr, "Error loading objects\n");
      return (1);
    }
  if ((mlx.mlx_ptr = mlx_init()) == NULL)
    {
      fprintf(stderr, "Error init mlx\n");
      return (1);
    }
  if ((mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, X, Y)) == NULL)
    {
      fprintf(stderr, "Error creating new image\n");
      return (1);
    }
  if ((mlx.data = mlx_get_data_addr(mlx.img_ptr,
				    &mlx.bpp,
				    &mlx.sizeline,
				    &mlx.endian)) == NULL)
    {
      fprintf(stderr, "Error getting info from mlx\n");
      return (1);
    }
  if ((mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, X, Y, "RTV1")) == NULL)
    {
      fprintf(stderr, "Error init window\n");
      return (1);
    }
  fill_image(&mlx, &eye, object_list);
  mlx_expose_hook(mlx.win_ptr, handle_expose, &mlx);
  mlx_key_hook(mlx.win_ptr, handle_key, 0);
  mlx_loop(mlx.mlx_ptr);
  return (0);
}
