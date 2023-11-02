/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibenhaim <ibenhaim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 18:22:59 by lmorel            #+#    #+#             */
/*   Updated: 2023/11/02 17:12:53 by ibenhaim         ###   ########.fr       */
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

// DEFINES
# define NAME "Cube3D"

	// UI PARAMS
# define MINMAP_ORIGIN_X 10
# define MINMAP_ORIGIN_Y 10
# define ENGINE_ORIGIN_X 0
# define ENGINE_ORIGIN_Y 0
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

	// PLAYER OPTIONS
# define VISION 90

	//MATHS
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
	int	e;
	int	left;
	int	right;
	int	m;
	int	shift;
	int	ctrl;
}	t_key;


typedef struct s_position
{
	float	x;
	float	y;
}	t_position;

typedef struct s_hit
{
	float	x;
	float	y;
	int		type;
	int		side;
	float	shade;
}	t_hit;

typedef struct s_player
{
	t_position	*pos;
	t_position	*dpos;
	float		speed;
	float		a;		//	angle
	int			size;
}	t_player;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*d;
	char	*f;
	char	*c;
}	t_textures;

typedef struct s_map
{
	char		*pathname;
	int			**map;
	int			height;
	int			*len;
	int			maxlen;
	int			minlen;
	int			player;

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
	int		width;
	int		height;
	int		offset;
	int		max_addr;
	double	ratio;
}	t_img_data;

typedef	struct s_wall
{
	int		type;
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

typedef struct s_tex
{
	t_img_data	*north;
	t_img_data	*south;
	t_img_data	*east;
	t_img_data	*west;
	t_img_data	*door;

	int			c;
	int			f;
}	t_tex;

typedef struct s_cube
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	int			bloc_size;	int			on;
	t_img_data	img_data;
	t_tex		tex;

	t_ray		*r;			// current ray
	t_map		*map;		// parsed data

	t_player	*player;

	t_key		*key;

	t_collector	*collector;

	int			ipx;
	int			ipy;
	int			ipx_add_xo;
	int			ipy_add_xo;
	int			ipx_sub_xo;
	int			ipy_sub_xo;
	int			ipx_right_xo;
	int			ipx_left_xo;
	int			ipy_right_xo;
	int			ipy_left_xo;
	float		tdis;

	int			door_count;

	int			count;
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
# define KEY_E 101
# define KEY_M 109
# define KEY_CTRL 65507
# define KEY_SHIFT 65505
// 					PROTOTYPES

// UTILS
void	free_gb(t_collector **lst);
int		add_address(t_collector **lst, void *address);
int		add_tab_to_gb(t_collector **lst, char **args);
int		keypress(int keycode, t_cube *cube);
int		error_exit(t_cube *cube, char *msg);
int		fexit(t_cube *cube);
int		commands(t_cube *cube);
int		keyrelease(int keycode, t_cube *cube);

// INIT
int		cube_init(t_cube *cube);
void	init_tex(t_cube *cube, char *path, t_img_data **img);

// DRAW
void	img_pixel_put(t_cube *cube, int x, int y, int color);
void	img_draw_line(t_cube *cube, t_position start, t_position end, int color);
void	img_square_put(t_cube *cube, int x, int y, int size, int color);
void	img_rect_put(t_cube *cube, t_position start, t_position end, int color);

// RENDER
void	draw_rays(t_cube *cube);
void	draw_3d_walls(t_cube *cube, int r, t_hit hit);
void	render_map(t_cube *cube);
int		renderer(t_cube *cube);
float	dist(float ax, float ay, float bx, float by);
void	handle_vertical_ray(t_cube *cube);
void	handle_horizontal_ray(t_cube *cube);
void	draw_rays(t_cube *cube);
int		is_dist_ok(t_cube *cube);
void	open_doors(t_cube *cube);

//	PARSING
int		parse_init(t_cube *cube, int argc, char **argv);
int		check_args(int argc, char **argv);
int		only_spaces(char *str);
int		parse_textures(t_cube *cube, char	**line);
int		read_colors(t_cube *cube);
int		parse_easy_map(t_cube *cube);
int		is_surrounded(t_cube *cube, int y, int x);
char	*skip_empty_lines(t_cube *cube);
int		check_player_pos(t_cube *cube, int i, int j);

// COLORS
# define RESET		"\033[00m"
# define BOLD		"\033[1m"
# define UNDERLINE 	"\033[4m"
# define GRAY		"\033[30m"
# define GREY		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BG_GRAY	"\033[40m"
# define BG_GREY	"\033[40m"
# define BG_RED		"\033[41m"
# define BG_GREEN	"\033[42m"
# define BG_YELLOW	"\033[43m"
# define BG_BLUE	"\033[44m"
# define BG_MAGENTA	"\033[45m"
# define BG_CYAN	"\033[46m"
# define BG_WHITE	"\033[47m"

#endif
