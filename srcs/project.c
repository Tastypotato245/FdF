/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 16:15:23 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/25 20:55:01 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// z is base
static void	rotate_x(int *y, int *z, double x_angle)
{
	int	prev_z;

	prev_z = *z;
	*z = prev_z * cos(x_angle) - *y * sin(x_angle);
	*y = prev_z * sin(x_angle) + *y * cos(x_angle);
}

// z is base
static void	rotate_y(int *x, int *z, double y_angle)
{
	int	prev_z;

	prev_z = *z;
	*z = prev_z * cos(y_angle) - *x * sin(y_angle);
	*x = prev_z * sin(y_angle) + *x * cos(y_angle);
}

static void	rotate_z(int *x, int *y, double z_angle)
{
	int	prev_x;

	prev_x = *x;
	*x = prev_x * cos(z_angle) - *y * sin(z_angle);
	*y = prev_x * sin(z_angle) + *y * cos(z_angle);
}

t_point	project(int x, int y, t_fdf *env)
{
	t_point	point;

	point.z = env->map->array[y][x][0];
	if (env->map->array[y][x][1] >= 0)
		point.color = env->map->array[y][x][1];
	else
		point.color = get_default_color(env->map->array[y][x][0], \
				env->map->z_min, env->map->z_max);
	point.x = x * env->camera->zoom;
	point.y = y * env->camera->zoom;
	point.z *= env->camera->zoom / env->camera->z_height;
	point.x -= (env->map->width * env->camera->zoom) / 2;
	point.y -= (env->map->height * env->camera->zoom) / 2;
	rotate_x(&point.y, &point.z, env->camera->x_angle);
	rotate_y(&point.x, &point.z, env->camera->y_angle);
	rotate_z(&point.x, &point.y, env->camera->z_angle);
	point.x += WIDTH / 2 + env->camera->x_offset;
	point.y += (HEIGHT + env->map->height / 2 * env->camera->zoom) / 2
		+ env->camera->y_offset;
	return (point);
}
