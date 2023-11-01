/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:31:27 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/11/01 19:32:11 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	get_side_wall(float a, int closer)
{
	if (a >= 0 && a < PI)
	{
		if (closer == 'h')
			return ('s');
		if (a >= 0 && a < P2)
			return ('w');
		else
			return ('e');
	}
	else
	{
		if (closer == 'h')
			return ('n');
		if (a >= PI && a < P3)
			return ('e');
		else
			return ('w');
	}
	return ('z');
}

t_hit	get_end_pos(t_cube *cube)
{
	t_hit	hit;

	if (cube->r->v->dis < cube->r->h->dis)
	{
		hit.x = cube->r->v->x;
		hit.y = cube->r->v->y;
		hit.type = cube->r->v->type;
		hit.side = get_side_wall(cube->r->a, 'v');
		hit.shade = 1;
		cube->tdis = cube->r->v->dis;
	}
	else
	{
		hit.x = cube->r->h->x;
		hit.y = cube->r->h->y;
		hit.type = cube->r->h->type;
		hit.side = get_side_wall(cube->r->a, 'h');
		hit.shade = 0.8;
		cube->tdis = cube->r->h->dis;
	}
	return (hit);
}

int	init_ray(t_cube *cube)
{
	cube->r = malloc(sizeof(t_ray) * 1);
	if (!cube->r || add_address(&cube->collector, cube->r) == 1)
		return (ft_putstr_fd("malloc error 1\n", 2), 1);
	cube->r->h = malloc(sizeof(t_wall) * 1);
	if (!cube->r->h || add_address(&cube->collector, cube->r->h) == 1)
		return (ft_putstr_fd("malloc error 2\n", 2), 1);
	cube->r->v = malloc(sizeof(t_wall) * 1);
	if (!cube->r->v || add_address(&cube->collector, cube->r->v) == 1)
		return (ft_putstr_fd("malloc error 3\n", 2), 1);
	if (VISION >= 2)
		cube->r->a = cube->player->a - (DR * VISION) / 2;
	else
		cube->r->a = cube->player->a;
	if (cube->r->a < 0)
		cube->r->a += 2 * PI;
	if (cube->r->a > 2 * PI)
		cube->r->a -= 2 * PI;
	cube->r->xo = 0;
	cube->r->yo = 0;
	cube->r->x = 0;
	cube->r->y = 0;
	return (0);
}

void	draw_rays(t_cube *cube)
{
	int			r;

	r = -1;
	init_ray(cube);
	while (++r < cube->win_width)
	{
		cube->r->h->dis = 1000000;
		cube->r->h->x = cube->player->pos->x;
		cube->r->h->y = cube->player->pos->y;
		handle_horizontal_ray(cube);
		cube->r->v->dis = 1000000;
		cube->r->v->x = cube->player->pos->x;
		cube->r->v->y = cube->player->pos->y;
		handle_vertical_ray(cube);
		draw_3d_walls(cube, r, get_end_pos(cube));
		cube->r->a += (DR * VISION) / cube->win_width;
		if (cube->r->a < 0)
			cube->r->a += 2 * PI;
		if (cube->r->a > 2 * PI)
			cube->r->a -= 2 * PI;
	}
}
