/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:34:06 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/11/14 15:19:21 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	read_textures(t_cube *cube)
{
	char	*line;
	char	**split;
	int		i;

	i = 0;
	while (i < 6)
	{
		line = get_next_line(cube->fd);
		if (!line || add_address(&cube->collector, line) == 1)
			return (ft_putstr_fd("get_next_line error\n", 2), 1);
		cube->count++;
		if (only_spaces(line) == 0)
		{
			split = ft_split(line, ' ');
			if (!split || add_tab_to_gb(&cube->collector, split) == 1)
				return (ft_putstr_fd("split error\n", 2), 1);
			if (parse_textures(cube, split) == 1)
				return (1);
			if (!(!ft_strncmp(split[0], "D", 2) \
				!= 0 && ft_strlen(split[0]) != 2))
				i++;
		}
	}
	return (0);
}

int	init_data(t_cube *cube, char *pathname)
{
	cube->win_height = WIN_HEIGHT;
	cube->win_width = WIN_WIDTH;
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
	cube->map->textures->d = NULL;
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
	printf(YELLOW"==========\tPARSING\t\t==========\n"RESET);
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
	if (parse_easy_map(cube) == 1)
		return (1);
	printf(GREEN"==========\tPARSING OK\t==========\n"RESET);
	return (0);
}
