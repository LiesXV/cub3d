/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 21:04:38 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/09 13:16:24 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float dist(float ax, float ay, float bx, float by)
{
	return ( sqrt ( (bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

//init structures and values
int	init_ray(t_cube *cube)
{
	cube->r = malloc(sizeof(t_ray) * 1);
	if (!cube->r || add_address(&cube->collector, cube->r) == 1)
		return (ft_putstr_fd("malloc error 1\n", 2), 1);
	cube->r->h = malloc(sizeof(t_wall) * 1);
	if (!cube->r->h || add_address(&cube->collector, cube->r->h) == 1)
		return (ft_putstr_fd("malloc error 2\n", 2), 1);
	cube->r->v = malloc(sizeof(t_wall) * 1);
	if (!cube->r->v || add_address(&cube->collector, cube->r->v) == 1)
		return (ft_putstr_fd("malloc error 3\n", 2), 1);
	if (VISION >= 2)
		cube->r->a = cube->player->a - DR * VISION / 2;	// ra ---> cube->r->a (r : ray) (a : angle) start with the leftest angle 
	else
		cube->r->a = cube->player->a;
	if (cube->r->a < 0)
		cube->r->a += 2 * PI;
	if (cube->r->a > 2 * PI)
		cube->r->a -= 2 * PI;
	cube->r->xo = 0;
	cube->r->yo = 0;
	cube->r->x = 0;
	cube->r->y = 0;
	return (0);
}

void	draw_3d_walls(t_cube *cube, int r, float tdis)
{
	float	ca;
	float	hline;
	float	oline;
	
	ca = cube->player->a - cube->r->a;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	tdis = tdis * cos(ca);
	hline = (cube->bloc_size * 320) / tdis;
	oline = 160 - hline / 2;
	if (hline > 320)
		hline = 320;
		
	t_position test;
	test.x = r * 8 + ENGINE_ORIGIN_X;
	test.y = oline + ENGINE_ORIGIN_Y;

	t_position test2;
	test2.x = r * 8 + ENGINE_ORIGIN_X;
	test2.y = oline + hline + ENGINE_ORIGIN_Y;
	
	img_draw_line(cube, test, test2, 0x0000ff);
}

void	draw_rays(t_cube *cube)
{
	int		r, mx, my, dof;
	float	tdis;

	init_ray(cube);
	r = 0;
	while (r < VISION)
	{
		// horizontal
		dof = 0;
		cube->r->h->dis = 100000;				//distance entre le player et le premier mur a l'horizontal
		cube->r->h->x = cube->player->pos->x;
		cube->r->h->y = cube->player->pos->y;
		if (cube->r->a > PI && cube->r->a < 2 * PI) 
		{
			cube->r->y = floor(cube->player->pos->y / cube->bloc_size) * cube->bloc_size;
			cube->r->x = cube->player->pos->x - (cube->player->pos->y - cube->r->y) / tan(cube->r->a);
			cube->r->yo = cube->bloc_size * -1;
			cube->r->xo = (cube->r->yo / tan(cube->r->a));
		}
		if (cube->r->a < PI)
		{
			cube->r->y = floor(cube->player->pos->y / cube->bloc_size) * cube->bloc_size + cube->bloc_size;
			cube->r->x = cube->player->pos->x - (cube->player->pos->y - cube->r->y) / tan(cube->r->a);
			cube->r->yo = cube->bloc_size;
			cube->r->xo = (cube->r->yo / tan(cube->r->a));
		}
		if (cube->r->a == 0 || cube->r->a == PI)
		{
			cube->r->x = cube->player->pos->x;
			cube->r->y = cube->player->pos->y;
			dof = cube->map->height * cube->map->len;
		}
		while (dof < cube->map->height * cube->map->len)
		{
			// printf("angle -> %f\n", cube->r->a);
			// printf("p pos %d %d\n", (int)cube->player->pos->x, (int)cube->player->pos->y);
			// printf("hitted %d %d\n", (int)cube->r->x, (int)cube->r->y);
			mx = cube->r->x / cube->bloc_size;
			my = cube->r->y / cube->bloc_size;
			// printf("map %d %d\n", (int)mx, (int)my);
			if (mx >= 0 && my >= 0 && my < cube->map->height && mx < cube->map->len && cube->map->map[my][mx] == 1)
			{
				cube->r->h->x = cube->r->x;
				cube->r->h->y = cube->r->y;
				cube->r->h->dis = dist(cube->player->pos->x, cube->player->pos->y, cube->r->h->x, cube->r->h->y);
				dof = cube->map->height * cube->map->len;
			}	
			else
			{
				cube->r->x += cube->r->xo;
				cube->r->y += cube->r->yo;
				dof += 1;
			}
		}

		// vertical
		cube->r->v->dis = 100000; 					//distance entre le player et le premier mur a la verticale
		cube->r->v->x = cube->player->pos->x;
		cube->r->v->y = cube->player->pos->y;
		dof = 0;
		if (cube->r->a > P2 && cube->r->a < P3) 
		{
			cube->r->x = floor(cube->player->pos->x / cube->bloc_size) * cube->bloc_size;
			cube->r->y = (cube->player->pos->x - cube->r->x) * -tan(cube->r->a) + cube->player->pos->y;
			cube->r->xo = -1 * cube->bloc_size;
			cube->r->yo = (-cube->r->xo * -tan(cube->r->a));
		}
		if (cube->r->a < P2 || cube->r->a > P3)
		{
			cube->r->x = floor(cube->player->pos->x / cube->bloc_size) * cube->bloc_size + cube->bloc_size;
			cube->r->y = (cube->player->pos->x - cube->r->x) * -tan(cube->r->a) + cube->player->pos->y;
			cube->r->xo = cube->bloc_size;
			cube->r->yo = (-cube->r->xo * -tan(cube->r->a));
		}
		if (cube->r->a == 0 || cube->r->a == PI)
		{
			cube->r->x = cube->player->pos->x;
			cube->r->y = cube->player->pos->y;
			dof = cube->map->height * cube->map->len;
		}
		while (dof < cube->map->height * cube->map->len)
		{
			// printf("angle -> %f\n", cube->r->a);
			// printf("p pos %d %d\n", (int)cube->player->pos->x, (int)cube->player->pos->y);
			// printf("hitted %d %d\n", (int)cube->r->x, (int)cube->r->y);
			mx = cube->r->x / cube->bloc_size;
			my = cube->r->y / cube->bloc_size;
			// printf("map %d %d\n", (int)mx, (int)my);
			if (mx >= 0 && my >= 0 && my < cube->map->height && mx < cube->map->len && cube->map->map[(int)my][(int)mx] == 1) //>= 0 && my >= 0 && my < cube->map->height && mx < cube->map->len 
			{
				cube->r->v->x = cube->r->x;
				cube->r->v->y = cube->r->y;
				cube->r->v->dis = dist(cube->player->pos->x, cube->player->pos->y, cube->r->v->x, cube->r->v->y);
				dof = cube->map->height * cube->map->len;
			}
			else
			{
				cube->r->x += cube->r->xo;
				cube->r->y += cube->r->yo;
				dof += 1;
			}
		}

		tdis = 0;

		t_position hit;
		int	color_ray = 0;
		if (cube->r->v->dis < cube->r->h->dis) // if vertical shortest
		{
			hit.y = cube->r->v->y;	
			if (cube->r->a > P2 && cube->r->a < P3)
				hit.x = cube->r->v->x + cube->bloc_size;
			else
				hit.x = cube->r->v->x;
			tdis = cube->r->v->dis;
			color_ray = 0xff0000;
		}
		if (cube->r->h->dis < cube->r->v->dis) // if horizontal shortest
		{
			hit.x = cube->r->h->x;
			if (cube->r->a < 2 * PI && cube->r->a > PI)
				hit.y = cube->r->h->y + cube->bloc_size;
			else
				hit.y = cube->r->h->y;
			tdis = cube->r->h->dis;
			color_ray = 0x00ff00;
		}

		t_position player_tmp;
		player_tmp.x = cube->player->pos->x + cube->player->size/2;
		player_tmp.y = cube->player->pos->y + cube->player->size/2;
		
		// display rays on minmap ; green = horizontal ; red = vertical
		img_draw_line(cube, player_tmp, hit, color_ray);
		
		//			draw 3D walls
		draw_3d_walls(cube, r, tdis);
		
		cube->r->a += DR; //	DR == 1 degree
		if (cube->r->a < 0)
			cube->r->a += 2 * PI;
		if (cube->r->a > 2 * PI)
			cube->r->a -= 2 * PI;
		r++;
	}
	// img_square_put(cube, test.x, test2.y, test2.x * test2.y, 0xffffff);
}

void	draw_min_player(t_cube *cube)
{
	t_position	min_pos;
	t_position	endline;

	
	min_pos.x = cube->player->pos->x;
	min_pos.y = cube->player->pos->y;
	img_square_put(cube, min_pos.x, min_pos.y, cube->player->size, 0xFED141);
	
	min_pos.x += cube->player->size/2;
	min_pos.y += cube->player->size/2;
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
			//printf("map %d, %d = %d\n", y, x, cube->map->map[y][x]);
			img_square_put(cube, x * cube->bloc_size, y * cube->bloc_size, cube->bloc_size, 0);
			if (cube->map->map[y][x] == 1)
			{
				// printf("asking square at : %d %d\n", x * size, y * size);
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
