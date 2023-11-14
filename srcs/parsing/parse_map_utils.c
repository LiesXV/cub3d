/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:00:01 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/11/14 15:36:22 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

void	skip_lines(t_cube *cube, int fd)
{
	char	*trash;

	cube->map->height = 0;
	while (1)
	{
		trash = get_next_line(fd);
		if (!trash || only_spaces(trash) == 1)
		{
			free(trash);
			break ;
		}
		free(trash);
		cube->map->height++;
	}
}

char	*skip_empty_lines(t_cube *cube)
{
	char	*line;
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
	skip_lines(cube, fd);
	close(fd);
	if (line[0] == 'D')
	{
		printf("put door textures\n");
		return (skip_empty_lines(cube));
	}
	return (line);
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
	if (cube->map->map[i][j] == '2' - 48 && !cube->map->textures->d)
		return (printf("you can't put doors without textures\n"), 1);
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

int	is_surrounded(t_cube *cube, int y, int x)
{
	if (x - 1 < 0 || cube->map->map[y][x - 1] == ' ')
		return (1);
	if (x + 1 > cube->map->len[y] - 1 || cube->map->map[y][x + 1] == ' ')
		return (1);
	if (y - 1 < 0 || cube->map->len[y - 1] < x || \
		cube->map->map[y - 1][x] == ' ')
		return (1);
	if (y + 1 > cube->map->height - 1 || cube->map->len[y + 1] < x - 1 \
		|| cube->map->map[y + 1][x] == ' ')
		return (1);
	return (0);
}
