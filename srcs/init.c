/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:18:28 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/13 16:34:18 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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

	y = 0;
	while (y < cube->map->height)
	{
		x = 0;
		while (x < cube->map->len)
		{
			if (cube->map->map[y][x] < 0)
			{
				cube->player->pos->x = x * cube->bloc_size + cube->bloc_size / 2;
				cube->player->pos->y = y * cube->bloc_size + cube->bloc_size / 2;;
				if (cube->map->map[y][x] == 'N' * -1)
					cube->player->a = 3 * PI / 2;
				else if (cube->map->map[y][x] == 'S' * -1)
					cube->player->a = PI / 2;
				else if (cube->map->map[y][x] == 'E' * -1)
					cube->player->a = 0;
				else if (cube->map->map[y][x] == 'W' * -1)
					cube->player->a = PI;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_player(t_cube *cube)
{
	cube->player->pos = malloc(sizeof(t_position) * 1);
	if (!cube->player->pos || add_address(&cube->collector, cube->player->pos) == 1)
		return (1);
	cube->player->dpos = malloc(sizeof(t_position) * 1);
	if (!cube->player->dpos || add_address(&cube->collector, cube->player->dpos) == 1)
		return (1);
	cube->player->size = cube->bloc_size / 3;
	cube->player->a = -1;
	find_player(cube);
	if (cube->player->a == -1)
		return (1);
	cube->player->dpos->x = cos(cube->player->a) * 5;
	cube->player->dpos->y = sin(cube->player->a) * 5;
	return (0);
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
		cube->bloc_size = (cube->win_width * 0.3) / cube->map->len;
	else
		cube->bloc_size = (cube->win_height * 0.3) / cube->map->height;
		//player
	if (init_player(cube) == 1)
		return (1);
		// keys
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
