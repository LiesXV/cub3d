NAME = cube3D

SRCS =	main.c srcs/hooks.c srcs/parsing.c

OBJS = $(SRCS:.c=.o)

HDRS = cube.h

LIBFT = libft/

LFTNAME	= libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3

RM = rm -rf

%.o : %.c $(HDRS) $(LIBFT)*.c $(LIBFT)libft.h Makefile
	$(CC) $(FLAGS) -Imlx_linux -O3 -c $< -o ${<:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	make -C mlx_linux
	$(CC) $(OBJS) ${LIBFT}${LFTNAME} -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	$(RM) $(OBJS)
	${MAKE} -C ${LIBFT} clean

fclean : clean
	$(RM) $(NAME)
	${MAKE} -C mlx_linux clean
	${MAKE} -C ${LIBFT} fclean

re : fclean all

.PHONY : all clean fclean re