/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:18:28 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/02 15:55:03 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	init_image(t_cube *cube, t_img_data *img)
{
	img->img = mlx_new_image(cube->mlx, cube->win_width, cube->win_height);
	img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->line_length, &img->endian);
	return (0);
}

void	find_player(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < cube->map->height)
	{
		x = 0;
		while (x < cube->map->len[y])
		{
			if (cube->map->map[y][x] < 0)
			{
				cube->player->pos->x = x * cube->bloc_size + cube->bloc_size / 2;
				cube->player->pos->y = y * cube->bloc_size + cube->bloc_size / 2;;
				if (cube->map->map[y][x] == 'N' * -1)
					cube->player->a = 3 * PI / 2;
				else if (cube->map->map[y][x] == 'S' * -1)
					cube->player->a = PI / 2;
				else if (cube->map->map[y][x] == 'E' * -1)
					cube->player->a = 0;
				else if (cube->map->map[y][x] == 'W' * -1)
					cube->player->a = PI;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_player(t_cube *cube)
{
	cube->player->pos = malloc(sizeof(t_position) * 1);
	if (!cube->player->pos || add_address(&cube->collector, cube->player->pos) == 1)
		return (1);
	cube->player->dpos = malloc(sizeof(t_position) * 1);
	if (!cube->player->dpos || add_address(&cube->collector, cube->player->dpos) == 1)
		return (1);
	cube->player->speed = 1.2;
	cube->player->size = cube->bloc_size / 3;
	cube->player->a = -1;
	find_player(cube);
	if (cube->player->a == -1)
		return (1);
	cube->player->dpos->x = cos(cube->player->a)* 5 / 4;
	cube->player->dpos->y = sin(cube->player->a)* 5 / 4;
	return (0);
}

int	rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	is_colors_valid(char **tab)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (ft_isdigit(tab[i][j]) == 0)
				return (1);
			j++;
		}
		color = ft_atoi(tab[i]);
		if (color < 0 || color > 255)
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

int	transform_colors(t_cube *cube, char *ceiling, char *floor)
{
	char	**strs;

	strs = ft_split(ceiling, ',');
	if (!strs || add_tab_to_gb(&cube->collector, strs) == 1)
		return (ft_putstr_fd(RED"split error\n"RESET, 2), 1);
	if (is_colors_valid(strs) == 1 || ceiling[ft_strlen(ceiling) - 1] == ',')
		return (printf("ceiling colors not valid"), 1);
	cube->tex.c = rgb_to_hex(ft_atoi(strs[0]), ft_atoi(strs[1]), ft_atoi(strs[2]));
	strs = ft_split(floor, ',');
	if (!strs || add_tab_to_gb(&cube->collector, strs) == 1)
		return (ft_putstr_fd(RED"split error\n"RESET, 2), 1);
	if (is_colors_valid(strs) == 1 || floor[ft_strlen(floor) - 1] == ',')
		return (printf("floor colors not valid"), 1);
	cube->tex.f = rgb_to_hex(ft_atoi(strs[0]), ft_atoi(strs[1]), ft_atoi(strs[2]));
	return (0);
}

int	cube_init(t_cube *cube)
{
	printf(YELLOW"==========\tINITIALISING\t==========\n"RESET);
	// values
	if (cube->map->maxlen >= cube->map->height)
		cube->bloc_size = (cube->win_width * 0.4) / cube->map->maxlen;
	else
		cube->bloc_size = (cube->win_height * 0.4) / cube->map->height;
	if (transform_colors(cube, cube->map->textures->c, cube->map->textures->f) != 0)
		return (1);
	printf(CYAN"  -> bloc size     : %d\n", cube->bloc_size);
	printf(CYAN"  -> ceiling color : #%x\n", cube->tex.c);
	printf(CYAN"  -> floor color   : #%x\n", cube->tex.f);
	// mlx initialisation
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
		return (1);
	cube->win = mlx_new_window(cube->mlx, cube->win_width, cube->win_height, NAME);
	if (cube->win == NULL)
		return (free(cube->mlx), 1);

	// image creation
	cube->img_data.img = NULL;
	init_image(cube, &cube->img_data);

	// text init
	init_tex(cube, cube->map->textures->no, &cube->tex.north);
	init_tex(cube, cube->map->textures->so, &cube->tex.south);
	init_tex(cube, cube->map->textures->ea, &cube->tex.east);
	init_tex(cube, cube->map->textures->we, &cube->tex.west);
	init_tex(cube, cube->map->textures->d, &cube->tex.door);

		//player
	if (init_player(cube) == 1)
		error_exit(cube, "malloc error.");
		// keys
	cube->key = malloc(sizeof(t_key) * 1);
	if (!cube->key || add_address(&cube->collector, cube->key) == 1)
		error_exit(cube, "malloc error.");
	cube->key->w = 0;
	cube->key->a = 0;
	cube->key->s = 0;
	cube->key->d = 0;
	cube->key->m = 0;
	cube->key->shift = 0;
	cube->key->ctrl = 0;
	cube->door_count = -1;
	printf(GREEN"==========\tINIT DONE\t==========\n"RESET);
	printf(RED"==========\tPLAYING\t\t==========\n"RESET);
	return (0);
}
