/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:18:28 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/14 18:54:27 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float	init_player_direction(int dir)
{
	if (dir == 'N' * -1)
		return (3 * PI / 2);
	else if (dir == 'S' * -1)
		return (PI / 2);
	else if (dir == 'E' * -1)
		return (0);
	else if (dir == 'W' * -1)
		return (PI);
	return (-1);
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
				cube->player->pos->x = x * cube->bloc_size
					+ cube->bloc_size / 2;
				cube->player->pos->y = y * cube->bloc_size
					+ cube->bloc_size / 2;
				cube->player->a = init_player_direction(cube->map->map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_player(t_cube *cube)
{
	if (cube->bloc_size < 5)
		cube->bloc_size = 5;
	cube->player->pos = malloc(sizeof(t_position) * 1);
	if (!cube->player->pos
		|| add_address(&cube->collector, cube->player->pos) == 1)
		return (1);
	cube->player->dpos = malloc(sizeof(t_position) * 1);
	if (!cube->player->dpos
		|| add_address(&cube->collector, cube->player->dpos) == 1)
		return (1);
	cube->player->speed = 1.2;
	cube->player->size = cube->bloc_size / 3;
	cube->player->a = -1;
	find_player(cube);
	if (cube->player->a == -1)
		return (1);
	cube->player->dpos->x = cos(cube->player->a) * 5 / 4;
	cube->player->dpos->y = sin(cube->player->a) * 5 / 4;
	return (0);
}

int	init_values(t_cube *cube)
{
	if (cube->map->maxlen >= cube->map->height)
		cube->bloc_size = (cube->win_width * 0.4) / cube->map->maxlen;
	else
		cube->bloc_size = (cube->win_height * 0.4) / cube->map->height;
	if (transform_colors(cube, cube->map->textures->c, cube->map->textures->f))
		return (1);
	if (init_player(cube) == 1)
		error_exit(cube, "malloc error.");
	printf(CYAN"  -> bloc size     : %d\n"RESET, cube->bloc_size);
	printf(CYAN"  -> ceiling color : #%x\n"RESET, cube->tex.c);
	printf(CYAN"  -> floor color   : #%x\n"RESET, cube->tex.f);
	cube->key = malloc(sizeof(t_key) * 1);
	if (!cube->key || add_address(&cube->collector, cube->key) == 1)
		error_exit(cube, "malloc error.");
	cube->key->w = 0;
	cube->key->a = 0;
	cube->key->s = 0;
	cube->key->d = 0;
	cube->key->m = 0;
	cube->key->left = 0;
	cube->key->right = 0;
	cube->key->shift = 0;
	cube->key->ctrl = 0;
	cube->door_count = -1;
	return (0);
}

int	cube_init(t_cube *cube)
{
	printf(YELLOW"==========\tINITIALISING\t==========\n"RESET);
	if (init_values(cube) != 0)
		return (1);
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
		return (1);
	cube->win = mlx_new_window(cube->mlx, WIN_WIDTH, WIN_HEIGHT, NAME);
	if (cube->win == NULL)
		return (free(cube->mlx), 1);
	cube->img_data.img = NULL;
	cube->tex.door = NULL;
	cube->tex.north = NULL;
	cube->tex.south = NULL;
	cube->tex.east = NULL;
	cube->tex.west = NULL;
	init_image(cube, &cube->img_data);
	init_tex(cube, cube->map->textures->no, &cube->tex.north);
	init_tex(cube, cube->map->textures->so, &cube->tex.south);
	init_tex(cube, cube->map->textures->ea, &cube->tex.east);
	init_tex(cube, cube->map->textures->we, &cube->tex.west);
	if (cube->map->textures->d)
		init_tex(cube, cube->map->textures->d, &cube->tex.door);
	printf(GREEN"==========\tINIT DONE\t==========\n"RESET);
	printf(RED"==========\tPLAYING\t\t==========\n"RESET);
	return (0);
}
