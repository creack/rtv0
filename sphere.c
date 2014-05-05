#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rt.h"
#include "get_next_line.h"

double			inter_sphere(t_vector *v, t_point *eye, t_object *object)
{
  double		k1;
  double		k2;
  t_sphere_infos	*s;

  s = (t_sphere_infos*)object;
  eye->x -= s->position.x;
  eye->y -= s->position.y;
  eye->z -= s->position.z;
  s->a = v->x * v->x + v->y * v->y + v->z * v->z;
  s->b = 2 * ((eye->x * v->x) + (eye->y * v->y) + (eye->z * v->z));
  s->c = (eye->x * eye->x) - (s->R * s->R);
  s->delta = s->b * s->b - 4 * s->a * s->c;
  s->obj.k = 0;

  eye->x += s->position.x;
  eye->y += s->position.y;
  eye->z += s->position.z;

  if (s->delta < 0)
    return (0);
  k1 = (-s->b + sqrt(s->delta)) / (2 * s->a);
  k2 = (-s->b - sqrt(s->delta)) / (2 * s->a);
  if (k1 < k2 && k1 > 0)
    {
      s->obj.k = k1;
      return (k1);
    }
  s->obj.k = k2;
  return (k2);
}

t_list			*parse_sphere(int fd, char **buf, t_list *next)
{
  t_sphere_infos	*s;

  s = malloc(1 * sizeof(*s));
  if (s == NULL)
    exit(1);
  memset(s, 0, sizeof(*s));
  free(*buf);
  while ((*buf = get_next_line(fd)) != NULL)
    {
      if (strncmp(*buf, "color=", 6) == 0)
	sscanf(*buf + 6, "%x\n", &s->obj.color);
      else if (strncmp(*buf, "x=", 2) == 0)
	sscanf(*buf + 2, "%d\n", &s->position.x);
      else if (strncmp(*buf, "y=", 2) == 0)
	sscanf(*buf + 2, "%d\n", &s->position.y);
      else if (strncmp(*buf, "z=", 2) == 0)
	sscanf(*buf + 2, "%d\n", &s->position.z);
      else if (strncmp(*buf, "R=", 2) == 0)
	sscanf(*buf + 2, "%d\n", &s->R);
      else
	break ;
      free(*buf);
    }
  return (new_object((t_object*)s, &inter_sphere, next));
}
