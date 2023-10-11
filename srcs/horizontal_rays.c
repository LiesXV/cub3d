/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_rays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:33:49 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/11 17:34:27 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_looking_up_or_down(t_cube *cube)
{
	float	atan;

	atan = -1 / tan(cube->r->a);
	if (cube->r->a > PI)
	{
		cube->r->y = (float)(((int)cube->player->pos->y \
			/ cube->bloc_size) * cube->bloc_size) - 0.0001;
		cube->r->x = (cube->player->pos->y - cube->r->y) \
			* atan + cube->player->pos->x;
		cube->r->yo = cube->bloc_size * -1;
		cube->r->xo = -cube->r->yo * atan;
	}
	else if (cube->r->a < PI)
	{
		cube->r->y = (float)(((int)cube->player->pos->y \
			/ cube->bloc_size) * cube->bloc_size) + cube->bloc_size;
		cube->r->x = (cube->player->pos->y - cube->r->y) \
			* atan + cube->player->pos->x;
		cube->r->yo = cube->bloc_size;
		cube->r->xo = -cube->r->yo * atan;
	}
	else
		return (1);
	return (0);
}

int	touch_a_wall_horizontal(t_cube *cube, int *dof)
{
	int	mx;
	int	my;

	mx = cube->r->x / cube->bloc_size;
	my = cube->r->y / cube->bloc_size;
	if (mx >= 0 && my >= 0 && my < cube->map->height && mx < cube->map->len \
		&& cube->map->map[(int)my][(int)mx] == 1)
	{
		cube->r->h->x = cube->r->x;
		cube->r->h->y = cube->r->y;
		cube->r->h->dis = dist(cube->player->pos->x, \
			cube->player->pos->y, cube->r->h->x, cube->r->h->y);
		*dof = cube->map->height * cube->map->len;
		return (0);
	}
	return (1);
}

void	handle_horizontal_ray(t_cube *cube)
{
	int	dof;


	dof = 0;
	if (is_looking_up_or_down(cube) == 1 \
		&& (cube->r->a == 0 || cube->r->a == PI))
	{
		cube->r->x = cube->player->pos->x;
		cube->r->y = cube->player->pos->y;
		dof = cube->map->height * cube->map->len;
	}
	while (dof < cube->map->height * cube->map->len)
	{
		if (touch_a_wall_horizontal(cube, &dof) == 1)
		{
			cube->r->x += cube->r->xo;
			cube->r->y += cube->r->yo;
			dof += 1;
		}
	}
}
