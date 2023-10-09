/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:22:59 by lmorel            #+#    #+#             */
/*   Updated: 2023/10/09 13:08:55 by ibenhaim         ###   ########.fr       */
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

	// UI PARAMS
# define MINMAP_MAX_SIZE 800
# define ENGINE_ORIGIN_X 1000
# define ENGINE_ORIGIN_Y 0

# define VISION 50
# define PI 3.14159265359
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533

// STRUCTS

typedef struct s_key
{
	int	w;
	int	a;
	int	s;
	int	d;
}	t_key;


typedef struct s_position
{
	float	x;
	float	y;
}	t_position;

typedef struct s_player
{
	t_position	*pos;
	t_position	*dpos;
	float		a;		//	angle
	int			size;
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
	int			**map;
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

typedef	struct	s_wall
{
	float	dis;
	float	x;
	float	y;
}	t_wall;

typedef struct s_ray
{
	float	x;
	float	y;
	float	a;
	float	xo;
	float	yo;
	t_wall	*h;	//horizontal
	t_wall	*v; //vertical
}	t_ray;

typedef struct s_cube
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	int			bloc_size;
	t_img_data	img_data;

	t_ray		*r;

	t_map		*map;

	t_player	*player;

	t_key		*key;

	t_collector	*collector;

	int			fd;
}	t_cube;

// KEYCODES
# define KEY_ESCAPE 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// 					PROTOTYPES

// UTILS
void	free_gb(t_collector **lst);
int		add_address(t_collector **lst, void *address);
int		add_tab_to_gb(t_collector **lst, char **args);
int		keypress(int keycode, t_cube *cube);
int		fexit(t_cube *cube);
int		commands(t_cube *cube);
int		keyrelease(int keycode, t_cube *cube);

// DRAW
void	img_draw_line(t_cube *cube, t_position start, t_position end, int color);
void	img_square_put(t_cube *cube, int x, int y, int size, int color);
void	draw_rays(t_cube *cube);
void	render_minmap(t_cube *cube);
int		renderer(t_cube *cube);

//	PARSING
int		init_cube(t_cube *cube, int argc, char **argv);
int		check_args(int argc, char **argv);
int		only_spaces(char *str);
int		parse_textures(t_cube *cube, char	**line);
int		read_colors(t_cube *cube);
int		parse_easy_map(t_cube *cube);

#endif
