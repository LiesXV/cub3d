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
	if (cube->win_width != 0)
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
	printf("width : %d\theight : %d", cube->win_width, cube->win_height);
	return (0);
}

// int	fill_texture(t_cube *cube, char **line, int face)
// {
// 	if (a)
// }

int	parse_first_line(t_cube *cube, char	**line)
{
	if (!ft_strncmp(line[0], "R", 2) != 0 && ft_strlen(line[0]) != 2)
		return (fill_resolution(cube, line));
	// if (!ft_strncmp(line[0], "NO", 3) != 0 && ft_strlen(line[0]) != 3)
	// 	return (fill_texture(cube, line, 1));
	// if (!ft_strncmp(line[0], "SO", 3) != 0 && ft_strlen(line[0]) != 3)
	// 	return (fill_texture(cube, line, 2));
	// if (!ft_strncmp(line[0], "WE", 3) != 0 && ft_strlen(line[0]) != 3)
	// 	return (fill_texture(cube, line, 3));
	// if (!ft_strncmp(line[0], "EA", 3) != 0 && ft_strlen(line[0]) != 3)
	// 	return (fill_texture(cube, line, 4));
	return (0);
}

int	read_lines(t_cube *cube)
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
		split = ft_split(line, ' ');
		if (!split || add_tab_to_gb(&cube->collector, split))
			return (ft_putstr_fd("split error\n", 2), 1);
		if (parse_first_line(cube, split) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_cube *cube, char *pathname)
{
	cube->fd = open(pathname, O_RDONLY);
	if (cube->fd < 0)
		return (1);
	if (read_lines(cube) == 1)
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
