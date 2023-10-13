/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:14:20 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/13 16:11:44 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_3d_walls(t_cube *cube, int r)
{
	float	ca;
	float	hline;
	float	oline;

	ca = cube->player->a - cube->r->a;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	cube->tdis = cube->tdis * cos(ca);
	hline = (cube->bloc_size * 320) / cube->tdis;
	oline = 160 - hline / 2;
	if (hline > 320)
		hline = 320;

		// DRAW BY LINES
	t_position top_wall;
	top_wall.x = r + ENGINE_ORIGIN_X;
	top_wall.y = oline + ENGINE_ORIGIN_Y + 120;

	t_position bot_wall;
	bot_wall.x = r + ENGINE_ORIGIN_X;
	bot_wall.y = oline + hline + ENGINE_ORIGIN_Y + 120;

	t_position bottom_win;
	bottom_win.x = r + ENGINE_ORIGIN_X;
	bottom_win.y = cube->win_height + 1000;
	
	img_draw_line(cube, bot_wall, bottom_win, 0x625973);	// ground
	img_draw_line(cube, top_wall, bot_wall, cube->color_tmp);

		// DRAW BY RECTANGLES
	// t_position test;
	// test.x = r * 8 - 4 + ENGINE_ORIGIN_X;
	// test.y = oline + ENGINE_ORIGIN_Y + 120;

	// t_position test2;
	// test2.x = r * 8 + 4 + ENGINE_ORIGIN_X;
	// test2.y = oline + hline + ENGINE_ORIGIN_Y + 120;
	
	// img_rect_put(cube, test, test2, cube->color_tmp);
}
