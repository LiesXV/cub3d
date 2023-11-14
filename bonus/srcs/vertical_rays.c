/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:34:44 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/11/14 19:25:17 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	is_looking_sides(t_cube *cube)
{
	float	ntan;

	ntan = -tan(cube->r->a);
	if (cube->r->a > (PI / 2) && cube->r->a < (3 * PI / 2))
	{
		cube->r->x = (float)(((int)cube->player->pos->x \
			/ cube->bloc_size) * cube->bloc_size) - 0.0001;
		cube->r->y = (cube->player->pos->x - cube->r->x) \
			* ntan + cube->player->pos->y;
		cube->r->xo = -cube->bloc_size;
		cube->r->yo = -cube->r->xo * ntan;
	}
	if (cube->r->a < (PI / 2) || cube->r->a > (3 * PI / 2))
	{
		cube->r->x = (float)(((int)cube->player->pos->x \
			/ cube->bloc_size) * cube->bloc_size) + cube->bloc_size;
		cube->r->y = (cube->player->pos->x - cube->r->x) \
			* ntan + cube->player->pos->y;
		cube->r->xo = cube->bloc_size;
		cube->r->yo = -cube->r->xo * ntan;
	}
	else
		return (0);
	return (1);
}

int	touch_a_wall_vertical(t_cube *cube, int *dof)
{
	int	mx;
	int	my;

	mx = cube->r->x / cube->bloc_size;
	my = cube->r->y / cube->bloc_size;
	if (mx >= 0 && my >= 0 && my < cube->map->height \
		&& mx < cube->map->len[(int)my]
		&& cube->map->map[(int)my][(int)mx] >= 1)
	{
		if (cube->map->map[(int)my][(int)mx] == 2)
			cube->r->v->type = 'd';
		else
			cube->r->v->type = 'w';
		cube->r->v->x = cube->r->x;
		cube->r->v->y = cube->r->y;
		cube->r->v->dis = dist(cube->player->pos->x, \
			cube->player->pos->y, cube->r->v->x, cube->r->v->y);
		*dof = cube->map->height * cube->map->len[(int)my] + 1;
		return (0);
	}
	return (1);
}

void	handle_vertical_ray(t_cube *cube)
{
	int	dof;

	dof = 0;
	if (is_looking_sides(cube) == 1 && (cube->r->a == 0 || cube->r->a == PI))
	{
		cube->r->x = cube->player->pos->x;
		cube->r->y = cube->player->pos->y;
		dof = cube->map->height * cube->map->minlen;
	}
	while (dof < cube->map->height * cube->map->minlen)
	{
		if (touch_a_wall_vertical(cube, &dof) == 1)
		{
			cube->r->x += cube->r->xo;
			cube->r->y += cube->r->yo;
			dof += 1;
		}
	}
}
