/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:23:04 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/18 13:37:26 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

char	*skip_empty_lines(t_cube *cube)
{
	char	*line;
	char	*trash;
	int		fd;

	cube->map->height = 0;
	fd = open(cube->map->pathname, O_RDONLY);
	line = get_next_line(cube->fd);
	if (!line || add_address(&cube->collector, line) == 1)
		return (ft_putstr_fd("get_next_line error\n", 2), NULL);
	cube->count++;
	while (line && only_spaces(line) == 1)
	{
		line = get_next_line(cube->fd);
		if (!line || add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), NULL);
		cube->count++;
	}
	while (++cube->map->height < cube->count)
		free(get_next_line(fd));
	cube->map->height = 0;
	while (1)
	{
		trash = get_next_line(fd);
		// printf("%s\n", trash);
		if (!trash || only_spaces(trash) == 1)
		{
			free(trash);
			break ;
		}
		free(trash);
		cube->map->height++;
	}
	close(fd);
	return (line);
}

int	is_surrounded(t_cube *cube, int y, int x)
{
	if (x - 1 < 0 || cube->map->map[y][x - 1] == ' ') // gauche
		return (1);
	if (x + 1 > cube->map->len[y] - 1 || cube->map->map[y][x + 1] == ' ') // droite
		return (1);
	if (y - 1 < 0 || cube->map->len[y - 1] < x || \
		cube->map->map[y - 1][x] == ' ') // haut
		return (1);
	if (y + 1 > cube->map->height - 1 || cube->map->len[y + 1] < x - 1 \
		|| cube->map->map[y + 1][x] == ' ') // bas
		return (1);
	return (0);
}

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

int	check_player_pos(t_cube *cube, int i, int j)
{
	if (cube->map->map[i][j] == ' ' - 48)
		cube->map->map[i][j] = ' ';
	if (cube->map->map[i][j] != '2' - 48 && cube->map->map[i][j] != '1' - 48 \
		&& cube->map->map[i][j] != '0' - 48 && cube->map->map[i][j] != ' ' \
			&& cube->map->map[i][j] != 'N' - 48 \
			&& cube->map->map[i][j] != 'E' - 48 \
			&& cube->map->map[i][j] != 'S' - 48 \
			&& cube->map->map[i][j] != 'W' - 48)
		return (1);
	if (cube->map->map[i][j] == 'S' - 48)
		cube->map->map[i][j] = 'S' * -1;
	else if (cube->map->map[i][j] == 'N' - 48)
		cube->map->map[i][j] = 'N' * -1;
	else if (cube->map->map[i][j] == 'E' - 48)
		cube->map->map[i][j] = 'E' * -1;
	else if (cube->map->map[i][j] == 'W' - 48)
		cube->map->map[i][j] = 'W' * -1;
	else
		return (0);
	cube->map->player++;
	if (cube->map->player > 1)
		return (ft_putstr_fd("too much players\n", 2), 1);
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
			return (printf("%d %d\n", i, j), ft_putstr_fd("unrecognized token in map\n", 2), 1);
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

int	parse_easy_map(t_cube *cube)
{
	char	*line;
	int		i;

	i = 0;
	cube->map->maxlen = 0;
	cube->map->minlen = 10000;
	line = skip_empty_lines(cube);
	if (!line)
		return (1);
	cube->map->map = malloc(sizeof(int *) * cube->map->height);
	if (!cube->map->map || add_address(&cube->collector, cube->map->map) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->map->len = malloc(sizeof(int) * cube->map->height);
	if (!cube->map->len || add_address(&cube->collector, cube->map->len) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->map->player = 0;
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
	printmap(cube); //print map
	if (is_map_closed(cube) == 1)
		return (ft_putstr_fd("map not closed\n", 2), 1);
	return (0);
}
