/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:49:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/04 03:41:39 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	keypress(int keycode, t_cube *cube)
{
	if (keycode == KEY_ESCAPE)
		fexit(cube);
	else if (keycode == KEY_W || keycode == KEY_UP)
	{
		cube->player->pos.x += cube->player->dpos.x;
		cube->player->pos.y += cube->player->dpos.y;
		renderer(cube);
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		cube->player->pos.x -= cube->player->dpos.x;
		cube->player->pos.y -= cube->player->dpos.y;
		renderer(cube);
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		cube->player->a -= 0.05;
		if (cube->player->a < 0)
			cube->player->a += 2*PI;
		cube->player->dpos.x = cos(cube->player->a) * 5;
		cube->player->dpos.y = sin(cube->player->a) * 5;
		renderer(cube);
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		cube->player->a += 0.05;
		if (cube->player->a > 2*PI)
			cube->player->a -= 2*PI;
		cube->player->dpos.x = cos(cube->player->a) * 5;
		cube->player->dpos.y = sin(cube->player->a) * 5;
		renderer(cube);
	}
	else
		printf("%d PRESSED !\n", keycode);
	return (0);
}
