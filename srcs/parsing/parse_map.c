/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:23:04 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/17 15:18:38 by ibenhaim         ###   ########.fr       */
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
		if (!trash)
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

int	is_map_closed(t_cube *cube, int y, int x)
{
	(void)cube;
	(void)y;
	(void)x;
	return (0);
}

int	add_line_to_map(t_cube *cube, char *line, int i)
{
	int	j;

	j = 0;
	cube->map->len[i] = ft_strlen(line) - 1;
	if (cube->map->len[i] > cube->map->maxlen)
		cube->map->maxlen = cube->map->len[i];
	if (cube->map->len[i] < cube->map->minlen)
		cube->map->minlen = cube->map->len[i];
	// printf("j = %d\n", j);
	cube->map->map[i] = ft_calloc(cube->map->len[i] + 1, sizeof(int));
	if (!cube->map->map[i] \
		|| add_address(&cube->collector, cube->map->map[i]) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	while (line[j])
	{
		cube->map->map[i][j] = line[j] - 48;
		if (cube->map->map[i][j] == 'N' - 48)
			cube->map->map[i][j] = 'N' * -1;
		else if (cube->map->map[i][j] == 'S' - 48)
			cube->map->map[i][j] = 'S' * -1;
		else if (cube->map->map[i][j] == 'E' - 48)
			cube->map->map[i][j] = 'E' * -1;
		else if (cube->map->map[i][j] == 'W' - 48)
			cube->map->map[i][j] = 'W' * -1;
		else if (cube->map->map[i][j] == ' ' - 48)
			cube->map->map[i][j] = ' ';
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
		while (i <= cube->map->len[j])
		{
			if (cube->map->map[j][i] == 'N' * -1)
				printf("N ");
			else if (cube->map->map[j][i] == 'S' * -1)
				printf("S ");
			else if (cube->map->map[j][i] == 'W' * -1)
				printf("W ");
			else if (cube->map->map[j][i] == 'E' * -1)
				printf("E ");
			else if (cube->map->map[j][i] == ' ')
				printf("  ");
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
	while (line && only_spaces(line) == 0)
	{
		if (add_line_to_map(cube, line, i) == 1)
			return (1);
		i++;
		line = get_next_line(cube->fd);
		if (add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), 1);
	}
	printmap(cube); //print map
	return (0);
}

// int	get_map_size(t_cube *cube)
// {
// 	char	**map;
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	// j = 0;
// 	// k = 0;
// 	printf("%s\n", cube->map->pathname);
// 	fd = open(cube->map->pathname, O_RDONLY);
// 	while (i > 0)
// 	{
// 		map[i] = get_next_line(fd);
// 		printf("map[%d] == %s\n", i, map[i]);
// 		if (!map[i])
// 			break ;
// 	}
// 	return (0);
// }

// int	parse_map(t_cube *cube)
// {
// 	if (get_map_size(cube) == 1)
// 		return (1);
// 	// if (is_map_closed(cube, 0, 0) == 1)
// 	// 	return (1);
// 	return (0);
// }
