/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:14:20 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/16 21:08:49 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_textures(t_cube *cube)
{
	// int bpp = cube->img_data.bits_per_pixel;
	// int ll = cube->img_data.line_length;
	// int end = cube->img_data.endian;
	cube->tex.tex_width = 1200;
	cube->tex.tex_height = 1200;

	// a securiser
	cube->tex.north = mlx_xpm_file_to_image(cube->mlx, "./textures/wall.xpm", &cube->tex.tex_width, &cube->tex.tex_height);
	//cube->tex.south = mlx_xpm_file_to_image(cube->mlx, cube->map->textures->so, &cube->tex.tex_width, &cube->tex.tex_height);
	//cube->tex.east = mlx_xpm_file_to_image(cube->mlx, cube->map->textures->ea, &cube->tex.tex_width, &cube->tex.tex_height);
	//cube->tex.west = mlx_xpm_file_to_image(cube->mlx, cube->map->textures->we, &cube->tex.tex_width, &cube->tex.tex_height);

	//cube->tex.north = mlx_get_data_addr(cube->tex.north, &bpp, &ll, &end);
	// cube->tex.south = mlx_get_data_addr(cube->tex.south, &bpp, &ll, &end);
	// cube->tex.east = mlx_get_data_addr(cube->tex.east, &bpp, &ll, &end);
	// cube->tex.west = mlx_get_data_addr(cube->tex.west, &bpp, &ll, &end);
	
	mlx_destroy_image(cube->mlx, cube->tex.north);
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
	
	int i;

	i = 0;
	while (i < hline)
	{
		//get_tex_pos();
		//get_tex_color();
		img_pixel_put(cube, top_wall.x, top_wall.y + i, cube->r->shade * 0xF58C8C);
		i++;
	}
	//img_draw_line(cube, top_wall, bot_wall, cube->color_tmp);
}
