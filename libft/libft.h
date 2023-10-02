/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:02:38 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/07/26 23:30:00 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	5
# endif

# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_list
{
	char			**cmd;
	char			*path;
	struct s_list	*next;
}					t_list;

/////////////////////// STRUCT /////////////////////////

void			free_split(char **split);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(char *s1, char *s2, unsigned int n);
char			*ft_strnstr(const char *str, const char *find, size_t len);
int				ft_atoi(const char *str);
long long int	ft_atoll(const char *str);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memcpy(void *dst, const void *src, size_t len);
void			ft_bzero(void *str, size_t len);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_substr_pipex(char const *s, unsigned int start, size_t len);
void			*ft_memset(void *str, int value, size_t len);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strfjoin(char *s1, char const *s2);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strdup(const char *str);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strncat(char *dst, const char *src, size_t size);
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_itoa(int n);
char			**ft_split(char const *s, char c);
char			**ft_split_pipex(char *str, char limiter);
// int				ft_lstsize(t_list *lst);
// t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmlast(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
// void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst);
int				ft_putstr(char *str);
int				ft_putchar(int c);
int				ft_putnbr(int nb);
int				ft_putpurcent(void);
int				ft_printf(const char *s, ...);
int				ft_putunsigned(unsigned int n);
void			ft_putnb_base(long long unsigned int nbr,
					long long unsigned int size, char *base, int *count);
int				ft_printptr(unsigned long long int nbr,
					unsigned long long int size, char *base);
char			*get_next_line(int fd);

#endif
