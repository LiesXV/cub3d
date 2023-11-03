/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:14:20 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/03 17:23:36 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	init_tex(t_cube *cube, char *path, t_img_data **img)
{
	ft_printf(CYAN"  -> %s", path);
	*img = malloc(sizeof(t_img_data));
	if (*img)
	{
		(*img)->img = mlx_xpm_file_to_image(cube->mlx, path,
				&(*img)->width, &(*img)->height);
		if (!(*img)->img)
		{
			ft_printf(RED"\t: KO\n"RESET);
			error_exit(cube, "invalid path.");
		}
		(*img)->addr = mlx_get_data_addr((*img)->img,
				&(*img)->bits_per_pixel, &(*img)->line_length, &(*img)->endian);
		(*img)->max_addr = (*img)->line_length * (*img)->height;
		(*img)->offset = (*img)->bits_per_pixel / 8;
		(*img)->ratio = (*img)->width / cube->bloc_size;
		ft_printf(GREEN"\t: OK\n"RESET);
	}
	else
		if (!(*img)->img)
			error_exit(cube, "malloc error.");
}

int	get_tex_color(t_img_data *img, int x, int y)
{
	int	*color;
	int	addr_index;

	addr_index = (y * img->line_length + x * img->offset);
	if (addr_index >= 0 && addr_index < img->max_addr)
	{
		color = (int *)(img->addr + addr_index);
		return (*color);
	}
	return (-1);
}

t_img_data	**get_tex_side(t_cube *cube, t_hit hit)
{
	if (hit.type == 'd')
		return (&cube->tex.door);
	else if (hit.type == 'w')
	{
		if (hit.side == 'n')
			return (&cube->tex.north);
		if (hit.side == 's')
			return (&cube->tex.south);
		if (hit.side == 'e')
			return (&cube->tex.east);
		if (hit.side == 'w')
			return (&cube->tex.west);
	}
	return (NULL);
}

float	ft_modf(float nbr, int div)
{
	int	i;

	i = nbr / div;
	nbr -= div * i;
	return (nbr);
}
