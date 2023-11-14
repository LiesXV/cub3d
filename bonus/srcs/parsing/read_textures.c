/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:49:14 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/11/03 13:21:07 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	put_door_texture(t_cube *cube, char *pathname)
{
	if (cube->map->textures->d != NULL)
		return (ft_putstr_fd("you cannot put two DOOR values\n", 2), 1);
	cube->map->textures->d = ft_strdup(pathname);
	if (!cube->map->textures->d \
		|| add_address(&cube->collector, cube->map->textures->d) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	return (0);
}

int	put_texture_end(t_cube *cube, char *pathname, int face)
{
	if (face == 3)
	{
		if (cube->map->textures->we != NULL)
			return (ft_putstr_fd("you cannot put two WEST values\n", 2), 1);
		cube->map->textures->we = ft_strdup(pathname);
		if (!cube->map->textures->we \
			|| add_address(&cube->collector, cube->map->textures->we) == 1)
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	else if (face == 4)
	{
		if (cube->map->textures->ea != NULL)
			return (ft_putstr_fd("you cannot put two EAST values\n", 2), 1);
		cube->map->textures->ea = ft_strdup(pathname);
		if (!cube->map->textures->ea \
			|| add_address(&cube->collector, cube->map->textures->ea) == 1)
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	else if (face == 5)
		return (put_door_texture(cube, pathname));
	return (0);
}

int	put_texture(t_cube *cube, char *pathname, int face)
{
	if (face == 1)
	{
		if (cube->map->textures->no != NULL)
			return (ft_putstr_fd("you cannot put two NORTH values\n", 2), 1);
		cube->map->textures->no = ft_strdup(pathname);
		if (!cube->map->textures->no \
			|| add_address(&cube->collector, cube->map->textures->no) == 1)
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	else if (face == 2)
	{
		if (cube->map->textures->so != NULL)
			return (ft_putstr_fd("you cannot put two SOUTH values\n", 2), 1);
		cube->map->textures->so = ft_strdup(pathname);
		if (!cube->map->textures->so \
			|| add_address(&cube->collector, cube->map->textures->so) == 1)
			return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	else if (face == 3 || face == 4 || face == 5)
		return (put_texture_end(cube, pathname, face));
	return (0);
}

int	fill_textures(t_cube *cube, char **line, int face)
{
	if (!line[1])
		return (ft_putstr_fd("path is missing\n", 2), 1);
	if (line[2])
		return (ft_putstr_fd("too much textures values\n", 2), 1);
	if (put_texture(cube, line[1], face) == 1)
		return (ft_putstr_fd("textures cannot be parsed\n", 2), 1);
	return (0);
}

int	parse_textures(t_cube *cube, char	**line)
{
	if (!ft_strncmp(line[0], "F", 2) != 0 && ft_strlen(line[0]) != 2)
		return (fill_colors(cube, line, 1));
	if (!ft_strncmp(line[0], "C", 2) != 0 && ft_strlen(line[0]) != 2)
		return (fill_colors(cube, line, 2));
	if (!ft_strncmp(line[0], "NO", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 1));
	if (!ft_strncmp(line[0], "D", 2) != 0 && ft_strlen(line[0]) != 2)
		return (fill_textures(cube, line, 5));
	if (!ft_strncmp(line[0], "SO", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 2));
	if (!ft_strncmp(line[0], "WE", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 3));
	if (!ft_strncmp(line[0], "EA", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 4));
	return (ft_putstr_fd("unrecognized line while parsing\n", 2), 1);
}
