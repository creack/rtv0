#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "rt.h"

t_parse_config	g_objects[] =
  {
    {"sphere", &parse_sphere},
    {"plan", &parse_plan},
    {0, 0}
  };

static int	xopen(const char *file, int flag)
{
  int		fd;

  fd = open(file, flag);
  if (fd < 0)
    {
      perror("Error opening file:");
      exit(1);
    }
  return (fd);
}

static int	is_config_header(char *buf)
{
  char		*brace_l;
  char		*brace_r;
  char		*sharp;

  brace_l = strchr(buf, '[');
  brace_r = strchr(buf, ']');
  sharp = strchr(buf, '#');
  if (brace_l && brace_r && brace_r > brace_l && (sharp > brace_r || !sharp))
    {
      *brace_r = '\0';
      return (brace_l - buf + 1);
    }
  return (-1);
}

static char	*end_parsing(char *buf, int parsed, int fd)
{
  if (buf == NULL)
    return (NULL);
  if (buf != NULL && parsed == 0)
    {
      free(buf);
      return (get_next_line(fd));
    }
  return (buf);
}

t_list		*new_object(t_object *obj, inter_fct fct, t_list *next)
{
  t_list	*new;

  new = malloc(1 * sizeof(*new));
  if (new == NULL)
    exit(1);
  memset(new, 0, sizeof(*new));
  new->obj = obj;
  new->fct = fct;
  new->next = next;
  return (new);
}

t_list		*load_objects()
{
  t_list	*new;
  int		fd;
  char		*buf;
  int		i;
  int		h;
  int		parsed;

  fd = xopen("rt.config", O_RDONLY);
  new = NULL;
  buf = get_next_line(fd);
  while (buf != NULL)
    {
      i = -1;
      parsed = 0;
      if ((h = is_config_header(buf)) != -1)
	{
	  while (parsed == 0 && g_objects[++i].name != 0)
	    if (!strcmp(g_objects[i].name, buf + h))
	      {
		new = g_objects[i].fct(fd, &buf, new);
		parsed = 1;
	      }
	}
      if ((buf = end_parsing(buf, parsed, fd)) == NULL)
	return (new);
    }
  return (new);
}
