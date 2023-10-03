/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:16:21 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/03 14:28:45 by ibenhaim         ###   ########.fr       */
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
	t_img_data img;
	img.img = NULL;
	img.img = mlx_new_image(cube->mlx, cube->win_width, cube->win_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	cube->img_data = &img;
	// values
	cube->player->y = cube->win_height / 2;
	cube->player->x = cube->win_width / 2;

	printf("init done\n");
	return (0);
}

void	img_pixel_put(t_img_data *img_data, int	x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + (y * img_data->line_length + x * (img_data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	img_square_put(t_img_data *img_data, int x, int y, int size, int color)
{
	int	y2;
	int	x2;

	y2 = y;
	while (y2 < y + size)
	{
		x2 = x;
		while (x2 < x + size)
		{
			img_pixel_put(img_data, x2, y2, color);
			x2++;
		}
		y2++;
	}
	printf("square done\n");
}

void	render_minmap(t_cube *cube)
{
	int	y;
	int	x;
	int	size = 50;
	int map[25] = {1, 1, 1, 1, 1,
					1, 0, 0, 0, 1,
			       1, 0, 4, 0, 1,
			       1, 0, 0, 0, 1,
			       1, 1, 1, 1, 1};


	y = 0;
	while (y < cube->map->height)
	{
		x = 0;
		while (x < cube->map->len)
		{
			printf("map %d = %d\n", (y * cube->map->len) + x, map[(y * cube->map->len) + x]);
			if (map[(y * cube->map->len) + x] == 1)
			{
				printf("asking square at : %d %d\n", x * size, y * size);
				img_square_put(cube->img_data, x * size, y * size, size, 255);
			}
			x++;
		}
		y++;
	}
	printf("minmap rendered\n");
}

int	renderer(t_cube *cube)
{
	render_minmap(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img_data->img, 0, 0);
	printf("image is on screen\n");
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
	mlx_key_hook(cube.win, keypress, &cube);
	mlx_hook(cube.win, 17, 0, fexit, &cube);
	mlx_loop(cube.mlx);
	free_gb(&cube.collector); //parsing in working..
	return (0);
}
