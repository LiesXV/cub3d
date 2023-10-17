/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:49:10 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/17 11:19:33 by ibenhaim         ###   ########.fr       */
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

int	parse_colors(t_cube *cube, char	**line)
{
	if (!ft_strncmp(line[0], "F", 2) != 0 && ft_strlen(line[0]) != 2)
		return (fill_colors(cube, line, 1));
	if (!ft_strncmp(line[0], "C", 2) != 0 && ft_strlen(line[0]) != 2)
		return (fill_colors(cube, line, 2));
	if (!ft_strncmp(line[0], "R", 2) != 0 && ft_strlen(line[0]) != 2)
		return (ft_putstr_fd("resolution (R) values already gifted\n", 2), 1);
	if (!ft_strncmp(line[0], "NO", 3) != 0 && ft_strlen(line[0]) != 3)
		return (ft_putstr_fd("north (NO) values already gifted\n", 2), 1);
	if (!ft_strncmp(line[0], "SO", 3) != 0 && ft_strlen(line[0]) != 3)
		return (ft_putstr_fd("south (SO) values already gifted\n", 2), 1);
	if (!ft_strncmp(line[0], "WE", 3) != 0 && ft_strlen(line[0]) != 3)
		return (ft_putstr_fd("west (WE) values already gifted\n", 2), 1);
	if (!ft_strncmp(line[0], "EA", 3) != 0 && ft_strlen(line[0]) != 3)
		return (ft_putstr_fd("east (EA) values already gifted\n", 2), 1);
	return (ft_putstr_fd("unrecognized line while parsing\n", 2), 1);
}

int	read_colors(t_cube *cube)
{
	int		i;
	char	*line;
	char	**split;

	i = 0;
	while (i < 2)
	{
		line = get_next_line(cube->fd);
		if (!line || add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), 1);
		cube->count++;
		if (only_spaces(line) == 0)
		{
			split = ft_split(line, ' ');
			if (!split || add_tab_to_gb(&cube->collector, split) == 1)
				return (ft_putstr_fd("split error\n", 2), 1);
			if (parse_colors(cube, split) == 1)
				return (1);
			i++;
		}
	}
	return (0);
}
