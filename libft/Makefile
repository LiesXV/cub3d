# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:52:55 by ibenhaim          #+#    #+#              #
#    Updated: 2023/09/09 17:29:25 by ibenhaim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a
FLAGS			= -Wall -Werror -Wextra -g3

HEADER			= libft.h
SRCS			= ft_isalpha.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isdigit.c ft_isalnum.c ft_isalpha.c \
				ft_isascii.c ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c \
				ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strcmp.c \
				ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_memchr.c ft_memcmp.c \
				ft_strtrim.c ft_strncat.c ft_strmapi.c ft_striteri.c  ft_putchar_fd.c  ft_putstr_fd.c ft_putendl_fd.c \
				ft_putnbr_fd.c ft_itoa.c ft_split.c ft_lstclear.c \
				ft_lstsize.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c get_next_line.c ft_printf.c \
				ft_putunsigned.c ft_utils.c ft_atoll.c ft_split_pipex.c ft_substr_pipex.c 
				
				

OBJS			= ${SRCS:.c=.o}

%.o:%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I .

all :	${NAME}

${NAME}: ${OBJS}
	${AR} rcs ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re