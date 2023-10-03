/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:22:59 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/03 11:08:34 by ibenhaim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

// INCLUDES
# include "mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>		//func : open
# include <unistd.h>	//func : close, read, write
# include <stdio.h>		//func : printf, perror
# include <string.h>	//func : strerror
# include <stdlib.h>	//func : malloc, free, exit
# include <math.h>

// PARAMS
# define NAME "Cube3D"
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000

// STRUCTS
typedef struct s_player
{
	float		x;		//player x pos
	float		y;		//player y pos
}	t_player;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
}	t_textures;

typedef struct s_map
{
	char		*pathname;
	int			*map;
	int			height;
	int			len;

	t_textures	*textures;
}	t_map;

typedef struct s_collector
{
	void				*address;
	struct s_collector	*next;
}	t_collector;

typedef struct s_img_data
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
	int			win_height;
	int			win_width;
	t_img_data	*img_data;

	t_map		*map;

	t_player	*player;

	t_collector	*collector;

	int			fd;
}	t_cube;

// KEYCODES
# define KEY_ESCAPE 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// PROTOTYPES
int		keypress(int keycode, t_cube *cube);
int		fexit(t_cube *cube);
int		parse_map(t_cube *cube, int argc, char **argv);
void	free_gb(t_collector **lst);
int		add_address(t_collector **lst, void *address);
int		add_tab_to_gb(t_collector **lst, char **args);

#endif
