/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:34:43 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/25 21:54:49 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
				draw_line(project(x, y, env), project(x + 1, y, env), env);
			if (y != map->height - 1)
				draw_line(project(x, y, env), project(x, y + 1, env), env);
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
				draw_line(project(x, y, env), project(x + 1, y, env), env);
			if (y != 0)
				draw_line(project(x, y, env), project(x, y - 1, env), env);
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
				draw_line(project(x, y, env), project(x - 1, y, env), env);
			if (y != map->height - 1)
				draw_line(project(x, y, env), project(x, y + 1, env), env);
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
				draw_line(project(x, y, env), project(x - 1, y, env), env);
			if (y != 0)
				draw_line(project(x, y, env), project(x, y - 1, env), env);
			--x;
		}
		--y;
	}
}

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
	if (flag.x == 1 && flag.y == 1)
		draw_px_py(env, map);
	else if (flag.x == -1 && flag.y == 1)
		draw_px_ny(env, map);
	else if (flag.x == 1 && flag.y == -1)
		draw_nx_py(env, map);
	else if (flag.x == -1 && flag.y == -1)
		draw_nx_ny(env, map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
