/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:16:21 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/09 20:03:00 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	fexit(t_cube *cube)
{
	printf("Freeing ...\n");
	if (cube->img_data.img)
	{
		mlx_destroy_image(cube->mlx, cube->img_data.img);
		printf("Image freed !\n");
	}
	mlx_destroy_window(cube->mlx, cube->win);
	printf("Exited successfully\n");
	exit(0);
	return (0);
}

int	renderer(t_cube *cube)
{
	render_floor_and_celling(cube);
	render_minmap(cube);
	draw_rays(cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->img_data.img, 0, 0);
	// printf("image is on screen\n");
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
	mlx_hook(cube.win, 2, (1L<<0), keypress, &cube);
	mlx_hook(cube.win, 3, (1L<<1), keyrelease, &cube);
	mlx_loop_hook(cube.win, renderer, &cube);
	mlx_loop(cube.mlx);
	free_gb(&cube.collector);
	return (0);
}
