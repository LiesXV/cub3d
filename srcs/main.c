/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:16:21 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/31 12:55:13 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	fexit(t_cube *cube)
{
	printf(YELLOW"==========\tCLOSING\t\t==========\n"RESET);
	printf(CYAN"  -> Freeing ...\n");
	if (cube->img_data.img)
	{
		mlx_destroy_image(cube->mlx, cube->img_data.img);
		printf("  -> Image freed !\n");
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

	if (parse_init(&cube, ac, av) == 1)
		return (free_gb(&cube.collector), 1);
	if (cube_init(&cube))
		return (free_gb(&cube.collector), 1);
	renderer(&cube);
	mlx_hook(cube.win, 2, (1L << 0), keypress, &cube);
	mlx_hook(cube.win, 3, (1L << 1), keyrelease, &cube);
	mlx_loop_hook(cube.mlx, renderer, &cube);
	mlx_loop(cube.mlx);
	free_gb(&cube.collector);
	get_next_line(-1);
	return (0);
}
