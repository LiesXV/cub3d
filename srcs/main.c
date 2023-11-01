/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:16:21 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/01 12:05:19 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	error_exit(t_cube *cube, char *msg)
{
	printf(RED"Error : "RESET);
	printf("%s\n", msg);
	if (cube->img_data.img)
		mlx_destroy_image(cube->mlx, cube->img_data.img);
	mlx_destroy_window(cube->mlx, cube->win);
	free_gb(&cube->collector);
	exit(1);
	return (1);
}

int	fexit(t_cube *cube)
{
	printf(YELLOW"==========\tCLOSING\t\t==========\n"RESET);
	printf(CYAN"  -> Freeing GB : ");
	free_gb(&cube->collector);
	printf(GREEN"OK\n");
	if (cube->img_data.img)
	{
		printf("  -> Image : ");
		mlx_destroy_image(cube->mlx, cube->img_data.img);
		printf(GREEN"OK\n"RESET);
	}
	mlx_destroy_window(cube->mlx, cube->win);
	printf(GREEN"==========\tEXIT SUCCESS\t==========\n"RESET);
	exit(0);
	return (0);
}

int	renderer(t_cube *cube)
{
	commands(cube);
	img_square_put(cube, ENGINE_ORIGIN_X, ENGINE_ORIGIN_Y, \
		cube->win_width - ENGINE_ORIGIN_X, cube->tex.c);
	draw_rays(cube);
	if (cube->key->m == 1)
		render_map(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img_data.img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	cube;

	if (parse_init(&cube, ac, av) || cube_init(&cube))
		return (free_gb(&cube.collector), 1);
	renderer(&cube);
	mlx_hook(cube.win, 2, (1L << 0), keypress, &cube);
	mlx_hook(cube.win, 3, (1L << 1), keyrelease, &cube);
	mlx_loop_hook(cube.mlx, renderer, &cube);
	mlx_loop(cube.mlx);
	get_next_line(-1);
	return (0);
}
