/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:04:38 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/04 03:50:12 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	draw_rays(t_cube *cube)
{
	int		r, mx, my, dof;
	float	rx, ry, ra, xo, yo;
	
	ra = cube->player->a;
	xo = 0;
	yo = 0;
	rx = 0;
	ry = 0;
	r = 0;
	while (r < 1)
	{
		// horizontal
		dof = 0;
		if (ra > PI && ra < 2 * PI) 
		{
			ry = floor(cube->player->pos.y / cube->bloc_size) * cube->bloc_size;
			rx = cube->player->pos.x - (cube->player->pos.y - ry) / tan(ra);
			yo = -cube->bloc_size;
			xo = (yo / tan(ra));
		}
		if (ra < PI)
		{
			ry = floor(cube->player->pos.y / cube->bloc_size) * cube->bloc_size + cube->bloc_size;
			rx = cube->player->pos.x - (cube->player->pos.y - ry) / tan(ra);
			yo = cube->bloc_size;
			xo = (yo / tan(ra));
		}
		if (ra == 0 || ra == PI)
		{
			rx = cube->player->pos.x;
			ry = cube->player->pos.y;
			dof = cube->map->height * cube->map->len;
		}
		while (dof < cube->map->height * cube->map->len)
		{
			printf("angle -> %f\n", ra);
			printf("p pos %d %d\n", (int)cube->player->pos.x, (int)cube->player->pos.y);
			printf("hitted %d %d\n", (int)rx, (int)ry);
			mx = rx / cube->bloc_size;
			my = ry / cube->bloc_size;
			printf("map %d %d\n", (int)mx, (int)my);
			if (mx >= 0 && my >= 0 && my < cube->map->height && mx < cube->map->len && cube->map->map[(int)my][(int)mx] == 1)
				dof = cube->map->height * cube->map->len;
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		
		t_position hit;
		hit.x = rx;
		if (ra < 2 * PI && ra > PI)
			hit.y = ry + cube->bloc_size;
		else
			hit.y = ry;
		
		t_position player_tmp;
		player_tmp.x = cube->player->pos.x + cube->player->size/2;
		player_tmp.y = cube->player->pos.y + cube->player->size/2;
		
		img_draw_line(cube, player_tmp, hit, 0xff0000);
		r++;
	}
}

void	draw_min_player(t_cube *cube)
{
	t_position	min_pos;
	t_position	endline;

	
	min_pos.x = cube->player->pos.x;
	min_pos.y = cube->player->pos.y;
	img_square_put(cube, min_pos.x, min_pos.y, cube->player->size, 0xFED141);
	
	min_pos.x += cube->player->size/2;
	min_pos.y += cube->player->size/2;
	endline.x = (min_pos.x + cube->player->dpos.x * 5);
	endline.y = (min_pos.y + cube->player->dpos.y * 5);
	img_draw_line(cube, min_pos, endline, 0xFED141);
	
	draw_rays(cube);
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
			//printf("map %d, %d = %d\n", y, x, cube->map->map[y][x]);
			img_square_put(cube, x * cube->bloc_size, y * cube->bloc_size, cube->bloc_size, 0);
			if (cube->map->map[y][x] == 1)
			{
				//printf("asking square at : %d %d\n", x * size, y * size);
				img_square_put(cube, x * cube->bloc_size, y * cube->bloc_size, cube->bloc_size - 2, 0x9999FF);
			}
			else
				img_square_put(cube, x * cube->bloc_size, y * cube->bloc_size, cube->bloc_size - 2, 0x1B2329);
			x++;
		}
		y++;
	}
	draw_min_player(cube);
	//printf("minmap rendered\n");
}
