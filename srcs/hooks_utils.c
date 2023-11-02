/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:29:05 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/11/02 15:57:46 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_dist_ok(t_cube *cube)
{
	int	xo;
	int	yo;
	int	xos;
	int	yos;

	xo = 0;
	yo = 0;
	xos = 0;
	yos = 0;
	if (cube->player->dpos->x < 0)
	{
		xo = -10;
		yos = 10;
	}
	else
	{
		xo = 10;
		yos = -10;
	}
	if (cube->player->dpos->y < 0)
	{
		yo = -10;
		xos = -10;
	}
	else
	{
		yo = 10;
		xos = 10;
	}
	cube->ipx = cube->player->pos->x / cube->bloc_size;
	cube->ipx_add_xo = (cube->player->pos->x + xo) / cube->bloc_size;
	cube->ipx_sub_xo = (cube->player->pos->x - xo) / cube->bloc_size;
	cube->ipx_right_xo = (cube->player->pos->x - xos) / cube->bloc_size;
	cube->ipx_left_xo = (cube->player->pos->x + xos) / cube->bloc_size;


	cube->ipy = cube->player->pos->y / cube->bloc_size;
	cube->ipy_add_xo = (cube->player->pos->y + yo) / cube->bloc_size;
	cube->ipy_sub_xo = (cube->player->pos->y - yo) / cube->bloc_size;
	cube->ipy_right_xo = (cube->player->pos->y - yos) / cube->bloc_size;
	cube->ipy_left_xo = (cube->player->pos->y + yos) / cube->bloc_size;

	return (0);
}

void	open_doors(t_cube *cube)
{
	if (cube->map->map[cube->ipy_add_xo][cube->ipx] == 2)
	{
		cube->map->map[cube->ipy_add_xo][cube->ipx] = -2;
		cube->door_count = 200;
	}
	else if (cube->map->map[cube->ipy_add_xo][cube->ipx] == -2 \
		&& cube->map->map[cube->ipy][cube->ipx] != -2)
		cube->map->map[cube->ipy_add_xo][cube->ipx] = 2;
	if (cube->map->map[cube->ipy][cube->ipx_add_xo] == 2)
	{
		cube->map->map[cube->ipy][cube->ipx_add_xo] = -2;
		cube->door_count = 200;
	}
	else if (cube->map->map[cube->ipy][cube->ipx_add_xo] == -2 \
		&& cube->map->map[cube->ipy][cube->ipx] != -2)
		cube->map->map[cube->ipy][cube->ipx_add_xo] = 2;
}
