/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:04:38 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/02 21:53:07 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt ((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_min_player(t_cube *cube)
{
	t_position	min_pos;
	t_position	ul_pos;
	t_position	endline;

	min_pos.x = cube->player->pos->x + MINMAP_ORIGIN_X;
	min_pos.y = cube->player->pos->y + MINMAP_ORIGIN_Y;
	ul_pos.x = min_pos.x - cube->player->size / 2;
	ul_pos.y = min_pos.y - cube->player->size / 2;
	img_square_put(cube, ul_pos, cube->player->size, 0xFED141);
	endline.x = (min_pos.x + cube->player->dpos->x * \
		(cube->player->size * 2.5));
	endline.y = (min_pos.y + cube->player->dpos->y * \
		(cube->player->size * 2.5));
	img_draw_line(cube, min_pos, endline, 0xFED141);
}

void	reset_map(t_cube *cube)
{
	t_position	base;
	t_position	end;

	base.x = MINMAP_ORIGIN_X - 2;
	base.y = MINMAP_ORIGIN_Y - 2;
	end.x = MINMAP_ORIGIN_X - 1 + (cube->map->maxlen) * cube->bloc_size;
	end.y = MINMAP_ORIGIN_Y - 1 + cube->map->height * cube->bloc_size;
	img_rect_put(cube, base, end, 0);
}

void	put_cube_map(t_cube *cube, int y, int x)
{
	t_position	origin;

	origin.x = x * cube->bloc_size + MINMAP_ORIGIN_X;
	origin.y = y * cube->bloc_size + MINMAP_ORIGIN_Y;
	if (cube->map->map[y][x] == 1)
		img_square_put(cube, origin, cube->bloc_size - 2, 0x9999FF);
	else if (cube->map->map[y][x] == 2)
		img_square_put(cube, origin, cube->bloc_size - 2, 0xFF0000);
	else if (cube->map->map[y][x] == -2)
		img_square_put(cube, origin, cube->bloc_size - 2, 0x660000);
	else if (cube->map->map[y][x] != ' ')
		img_square_put(cube, origin, cube->bloc_size - 2, 0x1B2329);
}

void	render_map(t_cube *cube)
{
	int	y;
	int	x;

	reset_map(cube);
	y = 0;
	while (y < cube->map->height)
	{
		x = 0;
		while (x < cube->map->len[y])
		{
			put_cube_map(cube, y, x);
			x++;
		}
		y++;
	}
	draw_min_player(cube);
}
