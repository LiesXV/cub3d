/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorel <lmorel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:22:59 by lmorel            #+#    #+#             */
/*   Updated: 2023/09/29 22:09:18 by lmorel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

// INCLUDES
# include <fcntl.h>		//func : open
# include <unistd.h>	//func : close, read, write
# include <stdio.h>		//func : printf, perror
# include <string.h>	//func : strerror
# include <stdlib.h>	//func : malloc, free, exit
# include <math.h>
# include "mlx_linux/mlx.h"

// PARAMS
# define NAME "Cube3D"
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000

// STRUCTS
typedef struct	s_img_data
{
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}	t_img_data;

typedef struct s_cube
{
	void		*mlx;
	void		*win;
	t_img_data	*img_data;

	int		*map;
	int		map_height;
	int		map_len;
	
	float	px;		//player x pos
	float	py;		//player y pos
}	t_cube;

// KEYCODES
# define KEY_ESCAPE 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// PROTOTYPES
int	keypress(int keycode, t_cube *cube);
int	fexit(t_cube *cube);

#endif