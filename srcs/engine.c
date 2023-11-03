/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:14:20 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/03 17:23:36 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_sky_ground(t_cube *cube, int r, float oline, float hline)
{
	t_position	top_wall;
	t_position	bot_wall;
	t_position	top_win;
	t_position	bottom_win;

	bottom_win.x = r + ENGINE_ORIGIN_X;
	bottom_win.y = cube->win_height + 1000;
	bot_wall.x = r + ENGINE_ORIGIN_X;
	bot_wall.y = oline + hline + ENGINE_ORIGIN_Y;
	img_draw_line(cube, bot_wall, bottom_win, cube->tex.f);
	top_wall.x = r + ENGINE_ORIGIN_X;
	top_wall.y = oline + ENGINE_ORIGIN_Y;
	top_win.x = r + ENGINE_ORIGIN_X;
	top_win.y = -5;
	img_draw_line(cube, top_wall, top_win, cube->tex.c);
}

void	draw_wall_textured(t_cube *cube, int r, float oline, float hline)
{
	int				i;
	int				tex_px;
	t_img_data		**texture;
	t_position		ratio;

	texture = get_tex_side(cube, cube->hit);
	if (cube->hit.side == 'n' || cube->hit.side == 's')
		ratio.x = ft_modf(cube->hit.x, cube->bloc_size) * ((*texture)->ratio);
	else
		ratio.x = ft_modf(cube->hit.y, cube->bloc_size) * ((*texture)->ratio);
	ratio.y = (*texture)->height / hline;
	i = 0;
	while (i < hline)
	{
		tex_px = get_tex_color(*texture, ratio.x, i * ratio.y);
		img_pixel_put(cube, r, oline + i, tex_px);
		i++;
	}
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
	hline = (cube->bloc_size * cube->win_height) / cube->tdis;
	oline = (cube->win_height / 2) - hline / 2;
	draw_sky_ground(cube, r, oline, hline);
	draw_wall_textured(cube, r, oline, hline);
}
