#ifndef __RT_H__
# define __RT_H__

# define X 700
# define Y 300

typedef struct	s_vector
{
  double	x;
  double	y;
  double	z;
}		t_vector;

typedef struct	s_point
{
  int		x;
  int		y;
  int		z;
}		t_point;

typedef struct	s_object
{
  unsigned int	color;
  double	k;
}		t_object;

typedef struct	s_sphere_infos
{
  t_object	obj;
  int		R;
  t_point	position;
  double	a;
  double	b;
  double	c;
  double	delta;
}		t_sphere_infos;

typedef struct	s_plan_infos
{
  t_object	obj;
  int		z;
}		t_plan_infos;

typedef struct	s_mlx
{
  void		*mlx_ptr;
  void		*win_ptr;
  void		*img_ptr;
  char		*data;
  int		sizeline;
  int		endian;
  int		bpp;
}		t_mlx;

typedef double (*inter_fct)(t_vector *v, t_point *eye, t_object *object);

typedef struct	s_list
{
  t_object	*obj;
  inter_fct	fct;
  struct s_list	*next;
}		t_list;

typedef t_list	*(*parse_fct)(int fd, char **buf, t_list *new);

typedef struct	s_parse_config
{
  char		*name;
  parse_fct	fct;
}		t_parse_config;


t_list	*load_objects();
t_list	*new_object(t_object *obj, inter_fct fct, t_list *next);

t_list	*parse_sphere(int fd, char **buf, t_list *next);
t_list	*parse_plan(int fd, char **buf, t_list *next);

void	fill_image(t_mlx *mlx, t_point *eye, t_list *object_list);
int	calc(int x, int y, t_point *eye, t_list *object_list);

#endif /* !__RT_H__ */
