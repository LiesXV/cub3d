/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:34:06 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/17 12:06:21 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

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
		// printf("line :%s\n", line);
		cube->count++;
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
	if (read_colors(cube) == 1)
		return (1);
	printf("NORTH :%s\tSOUTH :%s\tWEST :%s\tEAST :%s\n", cube->map->textures->no ,cube->map->textures->so ,cube->map->textures->we, cube->map->textures->ea);
	printf("CEILING :%s\tFLOOR :%s\n", cube->map->textures->c ,cube->map->textures->f);
	return (0);
}

int	init_data(t_cube *cube, char *pathname)
{
	cube->win_height = -1;
	cube->win_width = -1;
	cube->count = 0;
	cube->map->textures = malloc(sizeof(t_textures) * 1);
	if (!cube->map->textures \
		|| add_address(&cube->collector, cube->map->textures) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->player = malloc(sizeof(t_player) * 1);
	if (!cube->player \
		|| add_address(&cube->collector, cube->player) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	cube->map->textures->no = NULL;
	cube->map->textures->so = NULL;
	cube->map->textures->we = NULL;
	cube->map->textures->ea = NULL;
	cube->map->textures->f = NULL;
	cube->map->textures->c = NULL;
	cube->fd = open(pathname, O_RDONLY);
	if (cube->fd < 0)
		return (1);
	if (read_textures(cube) == 1)
		return (close(cube->fd), 1);
	return (0);
}

int	parse_init(t_cube *cube, int argc, char **argv)
{
	cube->collector = NULL;
	cube->map = malloc(sizeof(t_map) * 1);
	if (!cube->map || add_address(&cube->collector, cube->map) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	if (check_args(argc, argv) == 1)
		return (1);
	cube->map->pathname = ft_strdup(argv[1]);
	if (!cube->map->pathname \
		|| add_address(&cube->collector, cube->map->pathname) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	if (init_data(cube, argv[1]) == 1)
		return (1);
	// if (parse_map(cube) == 1)
	// 	return (1);
	if (parse_easy_map(cube) == 1)
		return (1);
	return (0);
}
