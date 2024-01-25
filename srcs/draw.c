/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:34:43 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/25 18:00:40 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

// little_endian
static void	put_pixel(t_fdf *env, int x, int y, int color)
{
	int		i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * env->bpp / 8) + (y * env->size_line);
		env->data_addr[i] = color;
		env->data_addr[++i] = color >> 8;
		env->data_addr[++i] = color >> 16;
	}
}

int	get_default_color(int z, int z_min, int z_max)
{
	double			percent;
	unsigned int	max;

	max = z_max - z_min;
	if (max == 0)
		return (0xFFFFFF);
	percent = ((double)(z - z_min) / max);
	if (percent < 0.2)
		return (0xFFFFFF);
	else if (percent < 0.4)
		return (0x79E5CB);
	else if (percent < 0.6)
		return (0x79E5CB);
	else if (percent < 0.8)
		return (0x79E5CB);
	else
		return (0x79E5CB);
}

static int	get_color(int x, t_point s, t_point e, float factor)
{
	int		r;
	int		g;
	int		b;

	x = 1;
	if (s.z > e.z)
	{
		r = (s.color >> 16) & 0xFF;
		g = (s.color >> 8) & 0xFF;
		b = s.color & 0xFF;
	}
	else
	{
		r = (e.color >> 16) & 0xFF;
		g = (e.color >> 8) & 0xFF;
		b = e.color & 0xFF;
	}
	r *= factor;
	g *= factor;
	b *= factor;
	return ((r << 16) | (g << 8) | b);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

// steep 0 < n <= 1
static void	bresenham_0(t_point s, t_point e, t_fdf *env, t_point dir)
{
	printf("!!! bresenham_0\n");
	int		f;
	int		df1;
	int		df2;
	t_point	m;
	t_point	d;

	d.y = ft_abs(e.y - s.y);
	d.x = ft_abs(e.x - s.x);
	m.x = s.x;
	m.y = s.y;
	f = 2 * d.y - d.x;
	df1 = 2 * d.y;
	df2 = 2 * (d.y - d.x);
	printf("What is the d.x : %d\n", d.x);
	printf("What is the d.y : %d\n", d.y);
	printf("What is the f : %d\n", f);
	printf("What is the df1 : %d\n", df1);
	printf("What is the df2 : %d\n", df2);
	printf("What is the dir.x : %d\n", dir.x);
	printf("What is the dir.y : %d\n", dir.y);
	fflush(stdout);
	while (m.x != e.x + dir.x)
	{
		put_pixel(env, m.x, m.y, get_color(m.x, s, e, 1));
		if (f < 0)
			f += df1;
		else
		{
			m.y += dir.y;
			f += df2;
		}
		m.x += dir.x;
	}
	printf("!!! bresenham_0 end\n");
}

// steep n > 1
static void	bresenham_1(t_point s, t_point e, t_fdf *env, t_point dir)
{
	printf("!!! bresenham_1\n");
	int		f;
	int		df1;
	int		df2;
	t_point	m;
	t_point	d;

	d.y = ft_abs(e.y - s.y);
	d.x = ft_abs(e.x - s.x);
	m.x = s.x;
	m.y = s.y;
	f = 2 * d.x - d.y;
	df1 = 2 * d.x;
	df2 = 2 * (d.x - d.y);
	printf("What is the d.x : %d\n", d.x);
	printf("What is the d.y : %d\n", d.y);
	printf("What is the f : %d\n", f);
	printf("What is the df1 : %d\n", df1);
	printf("What is the df2 : %d\n", df2);
	printf("What is the dir.x : %d\n", dir.x);
	printf("What is the dir.y : %d\n", dir.y);
	fflush(stdout);
	while (m.y != e.y + dir.y)
	{
		put_pixel(env, m.x, m.y, get_color(m.x, s, e, 1));
		if (f < 0)
			f += df1;
		else
		{
			m.x += dir.x;
			f += df2;
		}
		m.y += dir.y;
	}
	printf("!!! bresenham_1 end\n");
}

// branch
// draw_case == 1 : steep : n > 1 || n < -1
// draw_case == 0 : steep : 0 < n <= 1 || -1 <= n < 0
static void	draw_line(t_point s, t_point e, t_fdf *env)
{
	t_point	d;
	t_point	dir;

	printf("!!! draw line start\n");
	fflush(stdout);
	d.y = ft_abs(e.y - s.y);
	d.x = ft_abs(e.x - s.x);
	dir.x = -2 * (s.x > e.x) + 1;
	dir.y = -2 * (s.y > e.y) + 1;
	printf("What is the s.x : %d\n", s.x);
	printf("What is the s.y : %d\n", s.y);
	printf("What is the e.x : %d\n", e.x);
	printf("What is the e.y : %d\n", e.y);
	fflush(stdout);
	if (d.x != 0 && d.y / d.x > 1)
		bresenham_1(s, e, env, dir);
	else
		bresenham_0(s, e, env, dir);
	fflush(stdout);
}

static void	draw_px_py(t_fdf *env, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != map->width - 1)
				draw_line(project(x, y, env), project(x + 1, y, env), \
						env);
			if (y != map->height - 1)
				draw_line(project(x, y, env), project(x, y + 1, env), \
						env);
			++x;
		}
		++y;
	}
}

static void	draw_px_ny(t_fdf *env, t_map *map)
{
	int	x;
	int	y;

	y = map->height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != map->width - 1)
				draw_line(project(x, y, env), project(x + 1, y, env), \
						env);
			if (y != 0)
				draw_line(project(x, y, env), project(x, y - 1, env), \
						env);
			++x;
		}
		--y;
	}
}

static void	draw_nx_py(t_fdf *env, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = map->width - 1;
		while (x >= 0)
		{
			if (x != 0)
				draw_line(project(x, y, env), project(x - 1, y, env), \
						env);
			if (y != map->height - 1)
				draw_line(project(x, y, env), project(x, y + 1, env), \
						env);
			--x;
		}
		++y;
	}
}

static void	draw_nx_ny(t_fdf *env, t_map *map)
{
	int	x;
	int	y;

	y = map->height - 1;
	while (y >= 0)
	{
		x = map->width - 1;
		while (x >= 0)
		{
			if (x != 0)
				draw_line(project(x, y, env), project(x - 1, y, env), \
						env);
			if (y != 0)
				draw_line(project(x, y, env), project(x, y - 1, env), \
						env);
			--x;
		}
		--y;
	}
}

static void	draw_integrated(t_fdf *env, t_map *map, t_point flag)
{
	int	x;
	int	y;
	int x_temp;

	y = 0;
	if (flag.x == -1)
		y = map->height - 1;
	x_temp = 0;
	if (flag.y == -1)
		x_temp = map->width - 1;
	while (y < map->height && y >= 0)
	{
		x = x_temp;
		while (x < map->width && x >= 0)
		{
			if (x != map->width - 1)
				draw_line(project(x, y, env), project(x + flag.x, y, env), \
						env);
			if (y != map->height - 1)
				draw_line(project(x, y, env), project(x, y + flag.y, env), \
						env);
			x += flag.x;
		}
		y += flag.y;
	}
}

static void	draw_integrated(t_fdf *env, t_map *map, t_point flag)
{
	int	x;
	int	y;
	int x_temp;

	y = 0;
	if (flag.x == -1)
		y = map->height - 1;
	x_temp = 0;
	if (flag.y == -1)
		x_temp = map->width - 1;
	while (y < map->height && y >= 0)
	{
		x = x_temp;
		while (x < map->width && x >= 0)
		{
			if (x != map->width - 1)
				draw_line(project(x, y, env), project(x + flag.x, y, env), \
						env);
			if (y != map->height - 1)
				draw_line(project(x, y, env), project(x, y + flag.y, env), \
						env);
			x += flag.x;
		}
		y += flag.y;
	}
}
// draw switcher
void	drawer(t_map *map, t_fdf *env)
{
	t_point	flag;

	if (env->img != NULL)
		func_guard(mlx_destroy_image(env->mlx, env->img));
	env->img = null_guard(mlx_new_image(env->mlx, WIDTH, HEIGHT));
	env->data_addr = null_guard(mlx_get_data_addr(env->img, &env->bpp, \
				&env->size_line, &env->endian));
	flag.x = -2 * (env->camera->x_angle > 0) + 1;
	flag.y = -2 * (env->camera->y_angle > 0) + 1;
	draw_integrated(env, map, flag);
	fflush(stdout);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
