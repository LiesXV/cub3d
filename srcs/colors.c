/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:18:28 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/03 17:23:36 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	is_colors_valid(char **tab)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (ft_isdigit(tab[i][j]) == 0)
				return (1);
			j++;
		}
		color = ft_atoi(tab[i]);
		if (color < 0 || color > 255)
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

int	transform_colors(t_cube *cube, char *ceiling, char *floor)
{
	char	**strs;

	strs = ft_split(ceiling, ',');
	if (!strs || add_tab_to_gb(&cube->collector, strs) == 1)
		return (ft_putstr_fd(RED"split error\n"RESET, 2), 1);
	if (is_colors_valid(strs) == 1 || ceiling[ft_strlen(ceiling) - 1] == ',')
		return (printf("ceiling colors not valid"), 1);
	cube->tex.c = rgb_to_hex(ft_atoi(strs[0]),
			ft_atoi(strs[1]), ft_atoi(strs[2]));
	strs = ft_split(floor, ',');
	if (!strs || add_tab_to_gb(&cube->collector, strs) == 1)
		return (ft_putstr_fd(RED"split error\n"RESET, 2), 1);
	if (is_colors_valid(strs) == 1 || floor[ft_strlen(floor) - 1] == ',')
		return (printf("floor colors not valid"), 1);
	cube->tex.f = rgb_to_hex(ft_atoi(strs[0]),
			ft_atoi(strs[1]), ft_atoi(strs[2]));
	return (0);
}
