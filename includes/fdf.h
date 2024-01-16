/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:35:51 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/16 16:02:54 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../kyusulib/kyusulib.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>

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
	int	reverse;
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
	int			steep;
	t_map		*map;
	t_camera	*camera;
	t_mouse		*mouse;
}				t_fdf;

// parse.c
void			arg_checker(char *filename, t_map *map);

// utils.c
unsigned int	ft_atoi_base(const char *str, const char *base);

// mouse.c
int				ft_mouse_up(int button, int x, int y, void *params);
int				ft_mouse_down(int button, int x, int y, void *params);
int				ft_mouse_move(int x, int y, void *params);

// control.c
int				ft_close_win(void *params);
void			ft_hook_controls(t_fdf *env);
double			ft_reset_angles(double angle);

// keyboard.c
int				ft_key_press(int keycode, void *params);

#endif
