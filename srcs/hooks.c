/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:49:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/09 15:10:27 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	keypress(int keycode, t_cube *cube)
{
	if (keycode == KEY_ESCAPE)
		fexit(cube);
	else if (keycode == KEY_W || keycode == KEY_UP)
		cube->key->w = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cube->key->s = 1;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		cube->key->a = 1;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		cube->key->d = 1;
	else
		printf("%d PRESSED !\n", keycode);
	commands(cube);
	return (0);
}

int	is_dist_ok(t_cube *cube)
{
	int	xo;
	int yo;

	xo = 0;
	yo = 0;
	if (cube->player->dpos->x < 0)
		xo = -2;
	else
		xo = 2;
	if (cube->player->dpos->y < 0)	
		yo = -2;
	else
		yo = 2;
	cube->ipx = cube->player->pos->x / cube->bloc_size;
	cube->ipx_add_xo = (cube->player->pos->x + xo) / cube->bloc_size;
	cube->ipx_sub_xo = (cube->player->pos->x - xo) / cube->bloc_size;
	cube->ipy = cube->player->pos->y / cube->bloc_size;
	cube->ipy_add_xo = (cube->player->pos->y + yo) / cube->bloc_size;
	cube->ipy_sub_xo = (cube->player->pos->y - yo) / cube->bloc_size;
	return (0);
}

int	keyrelease(int keycode, t_cube *cube)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		cube->key->w = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cube->key->s = 0;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		cube->key->a = 0;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		cube->key->d = 0;
	commands(cube);
	return (0);
}

int	commands(t_cube *cube)
{
	is_dist_ok(cube);
	if (cube->key->w == 1)
	{
		// printf("from map[%d][%d] == %d to map[%d][%d] == %d\n", cube->ipy, cube->ipx_add_xo, cube->map->map[cube->ipy][cube->ipx_add_xo], cube->ipy_add_xo, cube->ipx, cube->map->map[cube->ipy_add_xo][cube->ipx]);
		if (!(cube->map->map[cube->ipy][cube->ipx_add_xo] == 1))
			cube->player->pos->x += cube->player->dpos->x;
		if (!(cube->map->map[cube->ipy_add_xo][cube->ipx] == 1))
			cube->player->pos->y += cube->player->dpos->y;
		renderer(cube);
	}
	else if (cube->key->s == 1)
	{
		if (!(cube->map->map[cube->ipy][cube->ipx_sub_xo] == 1))
			cube->player->pos->x -= cube->player->dpos->x;
		if (!(cube->map->map[cube->ipy_sub_xo][cube->ipx] == 1))
			cube->player->pos->y -= cube->player->dpos->y;
		renderer(cube);
	}
	else if (cube->key->a == 1)
	{
		cube->player->a -= 0.05;
		if (cube->player->a < 0)
			cube->player->a += 2 * PI;
		cube->player->dpos->x = cos(cube->player->a) * 5;
		cube->player->dpos->y = sin(cube->player->a) * 5;
		renderer(cube);
	}
	else if (cube->key->d == 1)
	{
		cube->player->a += 0.05;
		if (cube->player->a > 2 * PI)
			cube->player->a -= 2 * PI;
		cube->player->dpos->x = cos(cube->player->a) * 5;
		cube->player->dpos->y = sin(cube->player->a) * 5;
		renderer(cube);
	}
	return (0);
}

