/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:14:20 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/01 19:24:03 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_tex(t_cube *cube, char *path, t_img_data **img)
{
	ft_printf(CYAN"  -> %s");
	*img = malloc(sizeof(t_img_data));
	if (*img)
	{
		(*img)->img = mlx_xpm_file_to_image(cube->mlx, path, &(*img)->width, &(*img)->height);
		if (!(*img)->img)
		{
			ft_printf(RED"\t: KO\n"RESET);
			error_exit(cube, "invalid path.");
		}
		(*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bits_per_pixel, &(*img)->line_length, &(*img)->endian);
		(*img)->max_addr = (*img)->line_length * (*img)->height;
		(*img)->offset = (*img)->bits_per_pixel / 8;
		(*img)->ratio = (*img)->width / cube->bloc_size;
		ft_printf(GREEN"\t: OK\n"RESET);
	}
	else
		if (!(*img)->img)
			error_exit(cube, "malloc error.");
}

int	get_tex_color(t_img_data *img, int x, int y)
{
	int	*color;
	int	addr_index;

	addr_index = (y * img->line_length + x * img->offset);
	if (addr_index >= 0 && addr_index < img->max_addr)
	{
		color  = (int*)(img->addr + addr_index);
		return (*color);
	}
	return (-1);
}

t_img_data **get_tex_side(t_cube *cube, t_hit hit)
{
	if (hit.type == 'd')
		return (&cube->tex.door);
	else if (hit.type == 'w')
	{
		if (hit.side == 'n')
			return (&cube->tex.north);
		if (hit.side == 's')
			return (&cube->tex.south);
		if (hit.side == 'e')
			return (&cube->tex.east);
		if (hit.side == 'w')
			return (&cube->tex.west);
	}
	return (NULL);
}

static float	ft_modf(float nbr, int div)
{
	int	i;

	i = nbr / div;
	nbr -= div * i;
	return (nbr);
}

void	draw_3d_walls(t_cube *cube, int r, t_hit hit)
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
	oline = 160 - hline / 2;	

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

	img_draw_line(cube, bot_wall, bottom_win, cube->tex.f);	// ground


	// TEXTURES HANDELING

	int 			i;
	int 			tex_px;
	float			tex_col;
	t_img_data		**texture;
	t_position		ratio;

	texture = get_tex_side(cube, hit);
	if (hit.side == 'n' || hit.side == 's')
		tex_col = ft_modf(hit.x, cube->bloc_size);
	else
		tex_col = ft_modf(hit.y, cube->bloc_size);
	ratio.y = (*texture)->height / hline;
	ratio.x = (tex_col) * ((*texture)->ratio);
	i = 0;
	while (i < hline)
	{
		tex_px = get_tex_color(*texture, ratio.x, i * ratio.y);
		img_pixel_put(cube, top_wall.x, top_wall.y + i, tex_px);
		i++;
	}
}
