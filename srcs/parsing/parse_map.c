/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:23:04 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/03 14:10:01 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

char	*skip_empty_lines(t_cube *cube)
{
	char	*line;

	line = get_next_line(cube->fd);
	if (!line || add_address(&cube->collector, line) == 1)
		return (ft_putstr_fd("get_next_line error\n", 2), NULL);
	while (line && only_spaces(line) == 1)
	{
		line = get_next_line(cube->fd);
		if (!line || add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), NULL);
	}
	return (line);
}

int	add_line_to_map(t_cube *cube, char *line, int i)
{
	int		j;
	char	**split;

	split = ft_split(line, ' ');
	j = 0;
	cube->map->map[i] = malloc(sizeof(int) * 30);
	while (split[j] && cube->map->map[i][j])
	{
		cube->map->map[i][j] = ft_atoi(split[j]);
		j++;
	}
	return (0);
}

void	printmap(t_cube *cube)
{
	int	i;
	int	j;

	j = 0;
	while (j < cube->map->height)
	{
		i = 0;
		while (i < cube->map->len)
		{
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
	line = skip_empty_lines(cube);
	if (!line)
		return (1);
	while (line && only_spaces(line) == 0)
	{
		if (add_line_to_map(cube, line, i) == 1)
			return (1);
		i++;
		line = get_next_line(cube->fd);
		if (add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), 1);
	}
	printmap(cube);
	return (0);
}
