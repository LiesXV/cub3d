/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:34:06 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/02 14:34:06 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	finish_by_cub(char *path)
{
	int		pathlen;
	int		i;
	char	*cub;

	cub = "0buc.";
	pathlen = ft_strlen(path);
	i = 1;
	while (i < 5)
	{
		if (cub[i] != path[pathlen - i])
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
		return (ft_putstr_fd("error obtaining access to the map\n", 2), 1);
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

int	parse_map(int argc, char **argv)
{
	if (check_args(argc, argv) == 1)
		return (1);
	return (0);
}
