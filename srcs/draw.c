/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:14:40 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/02 22:16:02 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	init_image(t_cube *cube, t_img_data *img)
{
	img->img = mlx_new_image(cube->mlx, cube->win_width, cube->win_height);
	if (!img->img)
		error_exit(cube, "failure creating image");
	img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->line_length, &img->endian);
	return (0);
}

void	img_pixel_put(t_cube *cube, int x, int y, int color)
{
	char	*dst;

	dst = cube->img_data.addr + \
	(y * cube->img_data.line_length + x * (cube->img_data.bits_per_pixel / 8));
	if (x >= 0 && x < cube->win_width && y >= 0 && y < cube->win_height)
		*(unsigned int *)dst = color;
}

void	img_draw_line(t_cube *cube, t_position start, t_position end, int color)
{
	float	dx;
	float	dy;
	int		nb;

	dx = end.x - start.x;
	dy = end.y - start.y;
	nb = sqrt((dx * dx) + (dy * dy));
	dx /= nb;
	dy /= nb;
	while (nb--)
	{
		img_pixel_put(cube, start.x, start.y, color);
		start.x += dx;
		start.y += dy;
	}
}

void	img_square_put(t_cube *cube, t_position p, int size, int color)
{
	int	y2;
	int	x2;

	y2 = p.y;
	while (y2 < p.y + size)
	{
		x2 = p.x;
		while (x2 < p.x + size)
		{
			img_pixel_put(cube, x2, y2, color);
			x2++;
		}
		y2++;
	}
}

void	img_rect_put(t_cube *cube, t_position start, t_position end, int color)
{
	int	x;
	int	y;

	y = start.y;
	while (y <= end.y)
	{
		x = start.x;
		while (x <= end.x)
		{
			img_pixel_put(cube, x, y, color);
			x++;
		}
		y++;
	}
}
