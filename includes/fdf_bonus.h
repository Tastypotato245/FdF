/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:58:57 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/26 12:59:20 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../kyusulib/kyusulib.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080

# define ARROW_LEFT 123
# define ARROW_RIGHT 124
# define ARROW_DOWN 125
# define ARROW_UP 126
# define MINUS 27
# define PLUS 24
# define SPACE 49
# define KEY_R 15
# define MOUSE_CLICK_LEFT 1
# define MOUSE_CLICK_RIGHT 2
# define MOUSE_CLICK_MIDDLE 3
# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define ESCAPE 53

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}				t_point;

typedef struct s_map
{
	int	height;
	int	width;
	int	***array;
	int	z_max;
	int	z_min;
}				t_map;

typedef struct s_camera
{
	int		zoom;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	float	z_height;
	int		x_offset;
	int		y_offset;
	int		iso;
}				t_camera;

typedef struct s_mouse
{
	int		button;
	int		x;
	int		y;
	int		prev_x;
	int		prev_y;
}				t_mouse;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	t_map		*map;
	t_camera	*camera;
	t_mouse		*mouse;
}				t_fdf;

// parse.c
void			arg_checker(char *filename, t_map *map);

// utils.c
unsigned int	ft_atoi_base(const char *str, const char *base);
int				ft_min(int a, int b);
int				ft_abs(int n);

// mouse.c
int				mouse_up(int button, int x, int y, void *params);
int				mouse_down(int button, int x, int y, void *params);
int				mouse_move(int x, int y, void *params);

// control.c
int				close_win(void *params);
void			hook_controls(t_fdf *env);
double			reset_angles(double angle);

// keyboard.c
int				key_press(int keycode, void *params);

// draw.c
void			drawer(t_map *map, t_fdf *env);

// bresenham.c
void			draw_line(t_point s, t_point e, t_fdf *env);

// project.c
t_point			project(int x, int y, t_fdf *env);

// color.c
int				get_default_color(int z, int z_min, int z_max);
int				get_color(t_point e);

#endif
