/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 23:14:40 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/04 10:52:34 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	img_pixel_put(t_cube *cube, int	x, int y, int color)
{
	char	*dst;

	dst = cube->img_data.addr + (y * cube->img_data.line_length + x * (cube->img_data.bits_per_pixel / 8));
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

void	img_square_put(t_cube *cube, int x, int y, int size, int color)
{
	int	y2;
	int	x2;

	y2 = y;
	while (y2 < y + size)
	{
		x2 = x;
		while (x2 < x + size)
		{
			img_pixel_put(cube, x2, y2, color);
			x2++;
		}
		y2++;
	}
	//printf("square done\n");
}

void	img_rect_put(t_cube *cube, t_position start, t_position end, int color)
{
	int x;
	int y;

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
