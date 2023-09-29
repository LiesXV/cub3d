/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 19:49:17 by lmorel            #+#    #+#             */
/*   Updated: 2023/09/29 19:54:54 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	keypress(int keycode, t_cube *cube)
{
	if (keycode == KEY_ESCAPE)
		fexit(cube);
	else
		printf("%d PRESSED !\n", keycode);
	return (0);
}
