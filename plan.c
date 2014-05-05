#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "rt.h"
#include "get_next_line.h"

double		inter_plan(t_vector *v, t_point *eye, t_object *object)
{
  t_plan_infos	*p;

  p = (t_plan_infos*)object;
  p->obj.k = 0;
  if (v->z == 0)
    return (0);
  p->obj.k = -((eye->z + p->z) / v->z);
  if (p->obj.k < 0)
    return (0);
  return (p->obj.k);
}

t_list		*parse_plan(int fd, char **buf, t_list *next)
{
  t_plan_infos	*p;

  p = malloc(1 * sizeof(*p));
  if (p == NULL)
    exit(1);
  memset(p, 0, sizeof(*p));
  free(*buf);
  while ((*buf = get_next_line(fd)) != NULL)
    {
      if (strncmp(*buf, "color=", 6) == 0)
	sscanf(*buf + 6, "%x\n", &p->obj.color);
      else if (strncmp(*buf, "z=", 2) == 0)
	sscanf(*buf + 2, "%d\n", &p->z);
      else
	break ;
      free(*buf);
    }
  return (new_object((t_object*)p, &inter_plan, next));
}
