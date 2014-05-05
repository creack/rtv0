/*
** get_next_line.c for get_next_line in /u/epitech_2012/charme_g/cu/rendu/c/get_next_line
** 
** Made by guillaume charmes
** Login   <charme_g@epitech.net>
** 
** Started on  Fri Nov 23 11:33:12 2007 guillaume charmes
** Last update Sun Nov 25 22:33:59 2007 guillaume charmes
*/

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int	my_strlen(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    i++;
  return (i);
}

static int    	xwrite(int output, char *str, int len)
{
  int		i;
  char		*err;

  i = write(output, str, len);
  if (i < 0)
    {
      err = "Get Next Line Error : write error";
      xwrite(2, err, my_strlen(err));
      free(err);
      exit(-1);
    }
  return (i);
}

static void	*xmalloc(int size)
{
  void		*tmp;
  char		*err;

  tmp = malloc(size);
  if (tmp == NULL)
    {
      err = "Get Next Line Error : malloc error";
      xwrite(2, err, my_strlen(err));
      free(err);
      exit(-1);
    }
  return (tmp);
}

static int	xread(const int fd, char *buffer_read, int len)
{
  int		i;
  char		*err;

  i = read(fd, buffer_read, len);
  if (i < 0)
    {
      err = "Get Next Line Error : Read error";
      xwrite(2, err, my_strlen(err));
      free(err);
      exit(-1);
    }
  return (i);
}

char		*get_next_line(const int fd)
{
  static char	buffer_read[READ_BUFF];
  static int	i;
  static int	cursor;
  int		j;
  char		*buffer_return;

  j = 0;
  buffer_return = xmalloc(sizeof(*buffer_return) * (RETURN_BUFF + 1));
  cursor = (i == 0 ? xread(fd, buffer_read, READ_BUFF) : cursor);
  while (i <= cursor && j <= RETURN_BUFF)
    {
      if (j == RETURN_BUFF)
	return (buffer_return);
      if (buffer_read[i] == '\n')
	{
	  i++;
	  buffer_return[j] = '\0';
	  return (buffer_return);
	}
      cursor = (i >= cursor ? xread(fd, buffer_read, READ_BUFF) : cursor);
      i = (i >= cursor ? 0 : i);
      buffer_return[j++] = buffer_read[i++];
    }
  return (0);
}
