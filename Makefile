NAME = 	cub3D

SRCS_DIR = srcs/

SRCS =	main.c hooks.c engine.c init.c minmap.c draw.c parsing/parsing.c garbage_collector.c parsing/check_args.c parsing/read_colors.c parsing/read_textures.c parsing/parse_map.c \
		rays.c horizontal_rays.c vertical_rays.c parsing/parse_map_utils.c hooks_utils.c tex.c colors.c

SRCS_FILES = $(addprefix $(SRCS_DIR), $(SRCS))

OBJS = $(SRCS_FILES:.c=.o)

HDRS = cube.h

LIBFT = libft/

LFTNAME	= libft.a

CC = gcc

#FLAGS = -Wall -Wextra -Werror -O3 -Wno-deprecated-declarations -g3
FLAGS = -Wall -Werror -Wextra -Wno-deprecated-declarations -g3 
# -fsanitize=address 

RM = rm -rf

%.o : %.c $(HDRS) $(LIBFT)*.c $(LIBFT)libft.h Makefile
	$(CC) $(FLAGS) -Imlx_linux -O3 -c $< -o ${<:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	make -C libft
	make -C mlx_linux
	$(CC) ${FLAGS} $(OBJS) ${LIBFT}${LFTNAME} -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean :
	$(RM) $(OBJS)
	${MAKE} -C ${LIBFT} clean

fclean : clean
	$(RM) $(NAME)
	${MAKE} -C mlx_linux clean
	${MAKE} -C ${LIBFT} fclean

re : fclean all

.PHONY : all clean fclean re