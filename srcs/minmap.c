/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:04:38 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/11 17:35:19 by ibenhaim         ###   ########.fr       */
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
	t_position	endline;


	min_pos.x = cube->player->pos->x;
	min_pos.y = cube->player->pos->y;
	img_square_put(cube, min_pos.x, min_pos.y, cube->player->size, 0xFED141);

	min_pos.x += cube->player->size / 2;
	min_pos.y += cube->player->size / 2;
	endline.x = (min_pos.x + cube->player->dpos->x * 5);
	endline.y = (min_pos.y + cube->player->dpos->y * 5);
	img_draw_line(cube, min_pos, endline, 0xFED141);
}

void	render_minmap(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < cube->map->height)
	{
		x = 0;
		while (x < cube->map->len)
		{
			img_square_put(cube, \
				x * cube->bloc_size, y * cube->bloc_size, cube->bloc_size, 0);
			if (cube->map->map[y][x] == 1)
			{
				img_square_put(cube, x * cube->bloc_size, \
					y * cube->bloc_size, cube->bloc_size - 2, 0x9999FF);
			}
			else
				img_square_put(cube, x * cube->bloc_size, \
					y * cube->bloc_size, cube->bloc_size - 2, 0x1B2329);
			x++;
		}
		y++;
	}
	draw_min_player(cube);
}
