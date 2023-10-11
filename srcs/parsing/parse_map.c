/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:23:04 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/11 13:20:13 by ibenhaim         ###   ########.fr       */
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
	if (!split || add_tab_to_gb(&cube->collector, split) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	j = 0;
	cube->map->map[i] = malloc(sizeof(int) * 30);
	if (!cube->map->map[i] \
		|| add_address(&cube->collector, cube->map->map[i]) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	while (split[j] && cube->map->map[i][j])
	{
		cube->map->map[i][j] = ft_atoi(split[j]);
		if (cube->map->map[i][j] == 0 && !ft_strcmp(split[j], "N"))
			cube->map->map[i][j] = 'N' * -1;
		else if (cube->map->map[i][j] == 0 && !ft_strcmp(split[j], "S"))
			cube->map->map[i][j] = 'S' * -1;
		else if (cube->map->map[i][j] == 0 && !ft_strcmp(split[j], "E"))
			cube->map->map[i][j] = 'E' * -1;
		else if (cube->map->map[i][j] == 0 && !ft_strcmp(split[j], "W"))
			cube->map->map[i][j] = 'W' * -1;
		else if (cube->map->map[i][j] < 0) // si nombre negatif on considere c'est 0; possiblement erreur ? idk
			cube->map->map[i][j] = 0;
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
	printmap(cube); //print map
	return (0);
}

// int	is_map_closed(t_cube *cube, int y, int x)
// {
// 	if (y = 0)
// 	{
// 		if (cube->map->map[y][x + 1] == 1)
// 			return (is_map_closed(cube, y, x + 1));
// 		if (cube->map->map[y + 1][x] == 1)
// 			return (is_map_closed(cube, y + 1, x));
// 	}
// }

// int	parse_map(t_cube *cube)
// {
// 	if (is_map_closed(cube, 0, 0) == 1)
// 		return (1);
// }