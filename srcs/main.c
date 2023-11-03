/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:16:21 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/03 17:51:40 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	error_exit(t_cube *cube, char *msg)
{
	printf(RED"Error : "RESET);
	printf("%s\n", msg);
	free_tex(cube);
	mlx_destroy_window(cube->mlx, cube->win);
	free_gb(&cube->collector);
	get_next_line(-1);
	exit(1);
	return (1);
}

int	fexit(t_cube *cube)
{
	printf(YELLOW"==========\tCLOSING\t\t==========\n"RESET);
	printf(CYAN"  -> Freeing GB : ");
	printf(GREEN"OK\n");
	printf(CYAN"  -> Freeing images : ");
	free_tex(cube);
	printf(GREEN"OK\n"RESET);
	free_gb(&cube->collector);
	mlx_destroy_window(cube->mlx, cube->win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	printf(GREEN"==========\tEXIT SUCCESS\t==========\n"RESET);
	exit(0);
	return (0);
}

void	close_doors(t_cube *cube)
{
	int	x;
	int	y;

	y = 0;
	while (y < cube->map->height)
	{
		x = 0;
		while (x < cube->map->len[y])
		{
			x++;
			if (cube->map->map[y][x] == -2
				&& ((cube->ipy == y) && (cube->ipx == x)))
			{
				cube->door_count = 200;
				return ;
			}
			else if (cube->map->map[y][x] == -2)
				cube->map->map[y][x] = 2;
		}
		y++;
	}
	cube->door_count = -1;
}

int	renderer(t_cube *cube)
{
	commands(cube);
	draw_rays(cube);
	if (cube->door_count > 0)
		cube->door_count--;
	if (cube->door_count == 0)
		close_doors(cube);
	if (cube->key->m == 1)
		render_map(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img_data.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	cube;

	if (parse_init(&cube, ac, av))
		return (free_gb(&cube.collector), 1);
	cube_init(&cube);
	renderer(&cube);
	mlx_hook(cube.win, 2, (1L << 0), keypress, &cube);
	mlx_hook(cube.win, 3, (1L << 1), keyrelease, &cube);
	mlx_hook(cube.win, 17, 0, fexit, &cube);
	mlx_loop_hook(cube.mlx, renderer, &cube);
	mlx_loop(cube.mlx);
	get_next_line(-1);
	return (0);
}
