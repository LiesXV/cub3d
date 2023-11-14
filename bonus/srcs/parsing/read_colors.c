/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:49:10 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/11/14 13:26:18 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	put_color(t_cube *cube, char *color, int face)
{
	if (face == 1)
	{
		if (cube->map->textures->f != NULL)
			return (ft_putstr_fd("you cannot put two F color values\n", 2), 1);
		cube->map->textures->f = ft_strdup(color);
		if (!cube->map->textures->f \
			|| add_address(&cube->collector, cube->map->textures->f) == 1)
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	else if (face == 2)
	{
		if (cube->map->textures->c != NULL)
			return (ft_putstr_fd("you cannot put two C color values\n", 2), 1);
		cube->map->textures->c = ft_strdup(color);
		if (!cube->map->textures->c \
			|| add_address(&cube->collector, cube->map->textures->c) == 1)
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	return (0);
}

int	fill_colors(t_cube *cube, char **line, int face)
{
	if (!line[1])
		return (ft_putstr_fd("color is missing\n", 2), 1);
	if (line[2])
		return (ft_putstr_fd("too much colors values\n", 2), 1);
	if (put_color(cube, line[1], face) == 1)
		return (ft_putstr_fd("colors cannot be parsed\n", 2), 1);
	return (0);
}
