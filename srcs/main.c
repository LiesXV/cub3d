/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:16:21 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/09 13:18:21 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	fexit(t_cube *cube)
{
	printf("Freeing ...\n");
	//if (cube->img_data->img)
	//	mlx_destroy_image(cube->mlx, cube->img_data->img);
	mlx_destroy_window(cube->mlx, cube->win);
	printf("Exited successfully\n");
	exit(0);
	return (0);
}

int	init_image(t_cube *cube, t_img_data *img)
{
	img->img = mlx_new_image(cube->mlx, cube->win_width, cube->win_height);
	img->addr = mlx_get_data_addr(img->img, \
		&img->bits_per_pixel, &img->line_length, &img->endian);
	return (0);
}

void	find_player(t_cube *cube)
{
	int	y;
	int	x;

	cube->player->pos = malloc(sizeof(t_position) * 1);
	if (!cube->player->pos || add_address(&cube->collector, cube->player->pos) == 1)
		return ;
	cube->player->dpos = malloc(sizeof(t_position) * 1);
	if (!cube->player->dpos || add_address(&cube->collector, cube->player->dpos) == 1)
		return ;
	y = 0;
	while (y < cube->map->height)
	{
		x = 0;
		while (x < cube->map->len)
		{
			if (cube->map->map[y][x] == 4)
			{
				cube->player->pos->x = x * cube->bloc_size + cube->bloc_size / 3;
				cube->player->pos->y = y * cube->bloc_size + cube->bloc_size / 3;
				/*
				if (cube->map->map[y][x] == 'N') // define numbers for NSEW in map parsing
					cube->player->a = 3 * PI / 2;
				if (cube->map->map[y][x] == 'S')
					cube->player->a = PI / 2;
				if (cube->map->map[y][x] == 'E')
					cube->player->a = 0;
				if (cube->map->map[y][x] == 'W')
					cube->player->a = PI;
				*/
				return ;
			}
			x++;
		}
		y++;
	}
}

int	cube_init(t_cube *cube)
{
	// mlx initialisation
	cube->mlx = mlx_init();
	if (cube->mlx == NULL)
		return (1);
	cube->win = mlx_new_window(cube->mlx, cube->win_width, cube->win_height, NAME);
	if (cube->win == NULL)
		return (free(cube->mlx), 1);

	// image creation
	cube->img_data.img = NULL;
	init_image(cube, &cube->img_data);

	// values
	if (cube->map->len >= cube->map->height)
		cube->bloc_size = MINMAP_MAX_SIZE / cube->map->len;
	else
		cube->bloc_size = MINMAP_MAX_SIZE / cube->map->height;
	cube->player->size = cube->bloc_size / 3;
	find_player(cube);
	cube->player->a = 3 * PI / 2;
	cube->player->dpos->x = cos(cube->player->a) * 5;
	cube->player->dpos->y = sin(cube->player->a) * 5;
	cube->key = malloc(sizeof(t_key) * 1);
	if (!cube->key || add_address(&cube->collector, cube->key) == 1)
		return (1);
	cube->key->w = 0;
	cube->key->a = 0;
	cube->key->s = 0;
	cube->key->d = 0;
	printf("init done\n");
	return (0);
}

int	renderer(t_cube *cube)
{
	img_square_put(cube, ENGINE_ORIGIN_X, ENGINE_ORIGIN_Y, cube->win_width - ENGINE_ORIGIN_X, 0x000000);
	render_minmap(cube);
	draw_rays(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img_data.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	cube;

	if (init_cube(&cube, ac, av) == 1)
		return (free_gb(&cube.collector), 1);
	// printf("image is on screen\n");
	if (cube_init(&cube))
		return (1);
	renderer(&cube);
	mlx_hook(cube.win, 2, (1L<<0), keypress, &cube);
	mlx_hook(cube.win, 3, (1L<<1), keyrelease, &cube);
	mlx_loop_hook(cube.win, renderer, &cube);
	mlx_loop(cube.mlx);
	free_gb(&cube.collector);
	return (0);
}
