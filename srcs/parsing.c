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

int	fill_resolution(t_cube *cube, char **line)
{
	int	i;

	i = 0;
	if (!line[2])
		return (ft_putstr_fd("not enough resolution values\n", 2), 1);
	if (line[3])
		return (ft_putstr_fd("too much resolution values\n", 2), 1);
	if (cube->win_width != -1 || cube->win_height != -1)
		return (ft_putstr_fd("you cannot put two times R values\n", 2), 1);
	// printf("l\n");
	while (line[1][i])
	{
		if (ft_isdigit(line[1][i]) == 0 || i == 4)
			return (ft_putstr_fd("bad resolution values\n", 2), 1);
		i++;
	}
	cube->win_width = ft_atoi(line[1]);
	i = 0;
	while (line[2][i + 2])
	{
		if (ft_isdigit(line[2][i]) == 0 || i == 4)
			return (ft_putstr_fd("bad resolution values\n", 2), 1);
		i++;
	}
	cube->win_height = ft_atoi(line[2]);
	printf("width : %d\theight : %d\n", cube->win_width, cube->win_height);
	return (0);
}

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
	while (contains(str[i], " \t\n\r\v\f"))
		i++;
	if (i == (int)ft_strlen(str))
		return (1);
	return (0);
}

int	put_texture_end(t_cube *cube, char *pathname, int face)
{
	if (face == 3)
	{
		if (cube->map->textures->we != NULL)
			return (ft_putstr_fd("you cannot put two EAST values\n", 2), 1);
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
	else if (face == 3 || face == 4)
		return (put_texture_end(cube, pathname, face));
	return (0);
}

int	fill_textures(t_cube *cube, char **line, int face)
{
	if (!line[1])
		return (ft_putstr_fd("path is missing\n", 2), 1);
	if (line[2])
		return (ft_putstr_fd("too much textures values\n", 2), 1);
	printf("%s\n", line[1]);
	// if (access(line[1], F_OK) != 0)
	// 	return (ft_putstr_fd("path non-valid\n", 2), 1);
	if (put_texture(cube, line[1], face) == 1)
		return (ft_putstr_fd("textures cannot be parsed\n", 2), 1);
	return (0);
}

int	parse_textures(t_cube *cube, char	**line)
{
	if (!ft_strncmp(line[0], "S", 2) != 0 && ft_strlen(line[0]) != 2)
		return (ft_putstr_fd("map content should be at last\n", 2), 1);
	if (!ft_strncmp(line[0], "F", 2) != 0 && ft_strlen(line[0]) != 2)
		return (ft_putstr_fd("map content should be at last\n", 2), 1);
	if (!ft_strncmp(line[0], "C", 2) != 0 && ft_strlen(line[0]) != 2)
		return (ft_putstr_fd("map content should be at last\n", 2), 1);
	if (!ft_strncmp(line[0], "R", 2) != 0 && ft_strlen(line[0]) != 2)
		return (fill_resolution(cube, line));
	if (!ft_strncmp(line[0], "NO", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 1));
	if (!ft_strncmp(line[0], "SO", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 2));
	if (!ft_strncmp(line[0], "WE", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 3));
	if (!ft_strncmp(line[0], "EA", 3) != 0 && ft_strlen(line[0]) != 3)
		return (fill_textures(cube, line, 4));
	return (ft_putstr_fd("unrecognized line while parsing\n", 2), 1);
}

int	read_textures(t_cube *cube)
{
	char	*line;
	char	**split;
	int		i;

	i = 0;
	while (i < 5)
	{
		line = get_next_line(cube->fd);
		if (!line || add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), 1);
		printf("line :%s\n", line);
		if (only_spaces(line) == 0)
		{
			split = ft_split(line, ' ');
			if (!split || add_tab_to_gb(&cube->collector, split) == 1)
				return (ft_putstr_fd("split error\n", 2), 1);
			if (parse_textures(cube, split) == 1)
				return (1);
			i++;
		}
	}
	printf("NORTH :%s\tSOUTH :%s\tWEST :%s\tEAST :%s\n", cube->map->textures->no ,cube->map->textures->so ,cube->map->textures->we, cube->map->textures->ea);
	return (0);
}

int	init_data(t_cube *cube, char *pathname)
{
	cube->win_height = -1;
	cube->win_width = -1;
	cube->map = malloc(sizeof(t_map) * 1);
	if (!cube->map || add_address(&cube->collector, cube->map) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->map->textures = malloc(sizeof(t_textures) * 1);
	if (!cube->map->textures \
		|| add_address(&cube->collector, cube->map->textures) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->map->textures->no = NULL;
	cube->map->textures->so = NULL;
	cube->map->textures->we = NULL;
	cube->map->textures->ea = NULL;
	cube->fd = open(pathname, O_RDONLY);
	if (cube->fd < 0)
		return (1);
	if (read_textures(cube) == 1)
		return (close(cube->fd), 1);
	return (close(cube->fd), 0);
}

int	parse_map(t_cube *cube, int argc, char **argv)
{
	cube->collector = NULL;
	if (check_args(argc, argv) == 1)
		return (1);
	if (init_data(cube, argv[1]) == 1)
		return (1);
	return (0);
}
