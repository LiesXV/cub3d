/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:14:20 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/11 17:27:11 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	render_floor_and_celling(t_cube *cube)
{
	// sky
	t_position	engine_o;

	engine_o.x = ENGINE_ORIGIN_X;
	engine_o.y = ENGINE_ORIGIN_Y;
	img_square_put(cube, engine_o.x, engine_o.y, cube->win_width - engine_o.x, 0x91E8F0);

	// floor
	t_position	floor_start;
	t_position	floor_end;

	floor_start.x = ENGINE_ORIGIN_X;
	floor_start.y = ENGINE_ORIGIN_Y + cube->win_height * 0.4f;
	floor_end.x = cube->win_width;
	floor_end.y = ENGINE_ORIGIN_Y + cube->win_height;
	img_rect_put(cube, floor_start, floor_end, 0x625973);
}

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
	// t_position test;
	// test.x = r * 8 + ENGINE_ORIGIN_X;
	// test.y = oline + ENGINE_ORIGIN_Y;

	// t_position test2;
	// test2.x = r * 8 + ENGINE_ORIGIN_X;
	// test2.y = oline + hline + ENGINE_ORIGIN_Y;
	
	// img_draw_line(cube, test, test2, 0x0000ff);

		// DRAW BY RECTANGLES
	t_position test;
	test.x = r * 8 - 5 + ENGINE_ORIGIN_X;
	test.y = oline + ENGINE_ORIGIN_Y;

	t_position test2;
	test2.x = r * 8 + 5 + ENGINE_ORIGIN_X;
	test2.y = oline + hline + ENGINE_ORIGIN_Y;
	
	img_rect_put(cube, test, test2, 0x0000ff);
}
