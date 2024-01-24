/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:34:43 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/24 22:06:13 by kyusulee         ###   ########.fr       */
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
	float	percent;

	if (s.z > e.z)
	{
		r = (s.color >> 16) & 0xFF;
		g = (s.color >> 8) & 0xFF;
		b = s.color & 0xFF;
		r *= factor;
		g *= factor;
		b *= factor;
	}
	return ((r << 16) | (g << 8) | b);
}

static void	draw_line(t_point s, t_point e, t_fdf *env)
{
	t_point	m;
	t_point	dir;

	dir.x =  -2 * (s.x > e.x) + 1;
	dir.y =  -2 * (s.y > e.y) + 1;
	m.x = s.x;
	m.y = s.y;
	m.z = ((e.y - s.y + 1) + (e.x - s.x + 1) / 2 - 1) / (e.x - s.x + 1);
	dir.z = (e.x - s.x + 1) / m.z;
	while (m.x != e.x + x_dir)
	{
		while (m.y )
		{
			put_pixel(env, x, y, get_color(x, s, e, 1));
			m.y += y_dir;
		}
		m.x += x_dir;
	}
}

static void	draw_integrated(t_fdf *env, t_map *map, int x_flag, int y_flag)
{
	int	x;
	int	y;
	int x_temp;

	y = 0;
	if (x_flag == -1)
		y = map->height - 1;
	x_temp = 0;
	if (y_flag == -1)
		x_temp = map->width - 1;
	while (y < map->height && y >= 0)
	{
		x = x_temp;
		while (x < map->width && x >= 0)
		{
			if (x != map->width - 1)
				draw_line(project(x, y, env), project(x + x_flag, y, env), env);
			if (y != map->height - 1)
				draw_line(project(x, y, env), project(x, y + y_flag, env), env);
			x += x_flag;
		}
		y += y_flag;
	}
}

// draw switcher
void	drawer(t_map *map, t_fdf *env)
{
	int x_flag;
	int y_flag;

	if (env->img != NULL)
		func_guard(mlx_destroy_image(env->mlx, env->img));
	env->img = null_guard(mlx_new_image(env->mlx, WIDTH, HEIGHT));
	env->data_addr = null_guard(mlx_get_data_addr(env->img, &env->bpp, \
				&env->size_line, &env->endian));
	x_flag =  -2 * (env->camera->x_angle > 0) + 1;
	y_flag =  -2 * (env->camera->y_angle > 0) + 1;
	draw_integrated(env, map, x_flag, y_flag);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
