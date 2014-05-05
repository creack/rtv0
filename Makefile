NAME		=	rtv0
CC		=	gcc
SRCS		=	main.c		\
			fill_image.c	\
			get_next_line.c	\
			parse_conf.c	\
			sphere.c	\
			plan.c
HEADERS		=	rt.h		\
			get_next_line.h
OBJS		=	$(SRCS:.c=.o)
CFLAGS		=	-W -Wall -ansi -pedantic -I./minilibx -g3
LDFLAGS		=	-L./minilibx -lmlx -L /usr/X11/lib -lX11 -lXext -lm

$(NAME)		:	mlx $(OBJS) $(HEADERS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all		:	$(NAME)

mlx		:
		cd minilibx && make

clean		:
		$(RM) $(OBJS)
		$(RM) *~

fclean		:	clean
		$(RM) $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re

.SUFFIXES	:	.c .o .h
