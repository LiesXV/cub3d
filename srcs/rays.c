/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:31:27 by ibenhaim          #+#    #+#             */
/*   Updated: 2023/10/18 15:47:48 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

t_position	get_end_pos(t_cube *cube)
{
	t_position	hit;

	if (cube->r->v->dis < cube->r->h->dis)
	{
		hit.x = cube->r->v->x + MINMAP_ORIGIN_X;
		hit.y = cube->r->v->y + MINMAP_ORIGIN_Y;
		cube->tdis = cube->r->v->dis;
		cube->r->shade = 1;
	}
	if (cube->r->h->dis <= cube->r->v->dis)
	{
		hit.x = cube->r->h->x + MINMAP_ORIGIN_X;
		hit.y = cube->r->h->y + MINMAP_ORIGIN_Y;
		cube->tdis = cube->r->h->dis;
		cube->r->shade = 0.8;
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
	t_position	player_tmp;

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
		player_tmp.x = cube->player->pos->x + cube->player->size / 2 + MINMAP_ORIGIN_X;
		player_tmp.y = cube->player->pos->y + cube->player->size / 2 + MINMAP_ORIGIN_Y;
		img_draw_line(cube, player_tmp, get_end_pos(cube), 0x660000);
		draw_3d_walls(cube, r);
		cube->r->a += (DR * VISION) / cube->win_width;
		if (cube->r->a < 0)
			cube->r->a += 2 * PI;
		if (cube->r->a > 2 * PI)
			cube->r->a -= 2 * PI;
	}
}
