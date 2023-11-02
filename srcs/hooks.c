/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:49:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/02 15:43:36 by ibenhaim         ###   ########.fr       */
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
	else if (keycode == KEY_A)
		cube->key->a = 1;
	else if (keycode == KEY_D)
		cube->key->d = 1;
	else if (keycode == KEY_LEFT)
		cube->key->left = 1;
	else if (keycode == KEY_RIGHT)
		cube->key->right = 1;
	else if (keycode == KEY_CTRL && cube->key->shift == 0)
		cube->key->ctrl = 1;
	else if (keycode == KEY_SHIFT && cube->key->ctrl == 0)
		cube->key->shift = 1;
	else if (keycode == KEY_M && cube->key->m == 0)
		cube->key->m = 1;
	else if (keycode == KEY_M && cube->key->m == 1)
		cube->key->m = 0;
	else if (keycode == KEY_E)
		open_doors(cube);
	else // to remove
		printf("%d PRESSED !\n", keycode);
	return (0);
}

int	keyrelease(int keycode, t_cube *cube)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		cube->key->w = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cube->key->s = 0;
	else if (keycode == KEY_A)
		cube->key->a = 0;
	else if (keycode == KEY_D)
		cube->key->d = 0;
	else if (keycode == KEY_LEFT)
		cube->key->left = 0;
	else if (keycode == KEY_RIGHT)
		cube->key->right = 0;
	else if (keycode == KEY_SHIFT)
		cube->key->shift = 0;
	else if (keycode == KEY_CTRL)
		cube->key->ctrl = 0;
	return (0);
}

void	commands_next(t_cube *cube)
{
	if (cube->key->a == 1)
	{
		if (!(cube->map->map[cube->ipy][cube->ipx_left_xo] >= 1))
			cube->player->pos->x -= cos(cube->player->a + PI / 2) * cube->player->speed;
		if (!(cube->map->map[cube->ipy_left_xo][cube->ipx] >= 1))
			cube->player->pos->y -= sin(cube->player->a + PI / 2) * cube->player->speed;
	}
	if (cube->key->d == 1)
	{
		if (!(cube->map->map[cube->ipy][cube->ipx_right_xo] >= 1))
			cube->player->pos->x += cos(cube->player->a + PI / 2) * cube->player->speed;
		if (!(cube->map->map[cube->ipy_right_xo][cube->ipx] >= 1))
			cube->player->pos->y += sin(cube->player->a + PI / 2) * cube->player->speed;
	}
	if (cube->key->left == 1)
	{
		cube->player->a -= 0.05;
		if (cube->player->a < 0)
			cube->player->a += 2 * PI;
		cube->player->dpos->x = cos(cube->player->a) * 5 / 3;
		cube->player->dpos->y = sin(cube->player->a) * 5 / 3;
	}
	if (cube->key->right == 1)
	{
		cube->player->a += 0.05;
		if (cube->player->a > 2 * PI)
			cube->player->a -= 2 * PI;
		cube->player->dpos->x = cos(cube->player->a) * 5 / 3;
		cube->player->dpos->y = sin(cube->player->a) * 5 / 3;
	}
}

int	commands(t_cube *cube)
{
	is_dist_ok(cube);
	if (cube->key->ctrl == 1)
		cube->player->speed = 0.2;
	else if (cube->key->shift == 1)
		cube->player->speed = 1;
	if (cube->key->ctrl == 0 && cube->key->shift == 0)
		cube->player->speed = 0.6;
	if (cube->key->w == 1)
	{
		//printf("from map[%d][%d] == %d to map[%d][%d] == %d\n", cube->ipy, cube->ipx_add_xo, cube->map->map[cube->ipy][cube->ipx_add_xo], cube->ipy_add_xo, cube->ipx, cube->map->map[cube->ipy_add_xo][cube->ipx]);
		if (!(cube->map->map[cube->ipy][cube->ipx_add_xo] >= 1))
			cube->player->pos->x += cube->player->dpos->x * cube->player->speed;
		if (!(cube->map->map[cube->ipy_add_xo][cube->ipx] >= 1))
			cube->player->pos->y += cube->player->dpos->y * cube->player->speed;
	}
	if (cube->key->s == 1)
	{
		if (!(cube->map->map[cube->ipy][cube->ipx_sub_xo] >= 1))
			cube->player->pos->x -= cube->player->dpos->x * cube->player->speed;
		if (!(cube->map->map[cube->ipy_sub_xo][cube->ipx] >= 1))
			cube->player->pos->y -= cube->player->dpos->y * cube->player->speed;
	}
	commands_next(cube);
	return (0);
}
