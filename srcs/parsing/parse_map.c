/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:23:04 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/31 13:03:10 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	is_map_closed(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < cube->map->height)
	{
		while (x < cube->map->len[y])
		{
			if (cube->map->map[y][x] == '0' - 48 || \
				cube->map->map[y][x] == '2' - 48 || \
				cube->map->map[y][x] == 'N' * -1 || \
				cube->map->map[y][x] == 'E' * -1 || \
				cube->map->map[y][x] == 'W' * -1 || \
				cube->map->map[y][x] == 'S' * -1)
			{
				if (is_surrounded(cube, y, x) == 1)
					return (1);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	add_line_to_map(t_cube *cube, char *line, int i)
{
	int	j;

	j = 0;
	cube->map->len[i] = ft_strlen(line);
	if (cube->map->len[i] > cube->map->maxlen)
		cube->map->maxlen = cube->map->len[i];
	if (cube->map->len[i] < cube->map->minlen)
		cube->map->minlen = cube->map->len[i];
	cube->map->map[i] = ft_calloc(cube->map->len[i] + 1, sizeof(int));
	if (!cube->map->map[i] \
		|| add_address(&cube->collector, cube->map->map[i]) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	while (line[j])
	{
		cube->map->map[i][j] = line[j] - 48;
		if (check_player_pos(cube, i, j) == 1)
			return (printf("%d %d\n", i, j), \
				ft_putstr_fd("unrecognized token in map\n", 2), 1);
		j++;
	}
	return (0);
}

void	printmap(t_cube *cube)
{
	int	i;
	int	j;

	j = 0;
	printf("height %d, maxlen%d\n", cube->map->height, cube->map->maxlen);
	while (j < cube->map->height)
	{
		i = 0;
		while (i < cube->map->len[j])
		{
			if (cube->map->map[j][i] == 'N' * -1)
				printf("N ");
			else if (cube->map->map[j][i] == 'S' * -1)
				printf("S ");
			else if (cube->map->map[j][i] == 'W' * -1)
				printf("W ");
			else if (cube->map->map[j][i] == 'E' * -1)
				printf("E ");
			else
				printf("%d ", cube->map->map[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

int	alloc_tab(t_cube *cube)
{
	cube->map->maxlen = 0;
	cube->map->minlen = 10000;
	cube->map->map = malloc(sizeof(int *) * cube->map->height);
	if (!cube->map->map || add_address(&cube->collector, cube->map->map) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->map->len = malloc(sizeof(int) * cube->map->height);
	if (!cube->map->len || add_address(&cube->collector, cube->map->len) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->map->player = 0;
	return (0);
}

int	parse_easy_map(t_cube *cube)
{
	char	*line;
	int		i;

	i = 0;
	line = skip_empty_lines(cube);
	if (!line || alloc_tab(cube) == 1)
		return (1);
	while (line && only_spaces(line) == 0)
	{
		line = ft_strtrim(line, " ");
		if (add_line_to_map(cube, line, i) == 1 \
			|| add_address(&cube->collector, line) == 1)
			return (1);
		i++;
		line = get_next_line(cube->fd);
		if (add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), 1);
		if (!line)
			free(line);
	}
	if (cube->map->player < 1)
		return (ft_putstr_fd("no player in the map\n", 2), 1);
	// printmap(cube); //print map
	if (is_map_closed(cube) == 1)
		return (ft_putstr_fd("map not closed\n", 2), 1);
	return (0);
}
