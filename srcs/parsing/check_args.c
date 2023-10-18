/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:47:42 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/18 12:20:55 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	contains(char c, char *s)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

int	only_spaces(char *str)
{
	int	i;

	i = 0;
	while (contains(str[i], " \t\n\r\v\f\0"))
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

int	finish_by_cub(char *path)
{
	int		pathlen;
	int		i;
	char	*cub;

	cub = "buc.";
	pathlen = ft_strlen(path);
	i = 0;
	while (i < 4)
	{
		if (cub[i] != path[pathlen - 1 - i])
			return (ft_putstr_fd("format allowed : \".cub\" \n", 2), 1);
		i++;
	}
	return (0);
}

int	is_pathname_valid(char *path)
{
	if (finish_by_cub(path) == 1)
		return (1);
	if (access(path, R_OK) != 0)
		return (ft_putstr_fd("file non-existant or read-protected\n", 2), 1);
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (argc < 2)
		return (ft_putstr_fd("no map here\n", 2), 1);
	else if (argc > 2)
		return (ft_putstr_fd("too much arguments\n", 2), 1);
	if (is_pathname_valid(argv[1]) == 1)
		return (ft_putstr_fd("pathname not valid\n", 2), 1);
	return (printf("path of the map: %s\n", argv[1]), 0);
}
