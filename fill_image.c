#include <mlx.h>
#include <stdio.h>

#include "rt.h"

void	my_pixel_put_to_image(t_mlx *mlx, int x, int y, unsigned long color)
{
  int	i;
  int	j;
  char	clr[4];

  if (x < 0 || y < 0 || x >= X || y >= Y)
    return ;
  clr[3] = color / 16777216;
  clr[2] = color / 65536;
  clr[1] = color / 256;
  clr[0] = color % 256;
  j = (mlx->bpp / 8);
  while (j)
    {
      --j;
      i = ((mlx->sizeline * y) + (4 * x) + j);
      mlx->data[i] = clr[j];
    }
}

void	fill_image(t_mlx *mlx, t_point *eye, t_list *object_list)
{
  int	i;
  int	x;
  int	y;

  i = 0;
  while (i < X * Y)
    {
      x = i % X;
      y = i / X;
      if (x == 0 && y % 10 == 0)
      	printf("Processing: %d%%\n", (int)(((float)y / (float)Y) * 100) + 1);
      my_pixel_put_to_image(mlx, x, y, calc(x, y, eye, object_list));
      i++;
    }
}
