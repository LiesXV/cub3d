NAME = cube3D

SRCS =	main.c srcs/hooks.c

OBJS = $(SRCS:.c=.o)

HDRS = cube.h

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3

RM = rm -rf

%.o : %.c $(HDRS) Makefile
	$(CC) $(FLAGS) -Imlx_linux -O3 -c $< -o ${<:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re