/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:56:23 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/24 17:10:21 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int	close_win(void *params)
{
	t_fdf	*env;
	int		x;
	int		y;

	env = (t_fdf *)params;
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	free(env->camera);
	free(env->mouse);
	y = -1;
	while (++y < env->map->height)
	{
		x = -1;
		while (++x < env->map->width)
			free(env->map->array[y][x]);
		free(env->map->array[y]);
	}
	free(env->map->array);
	free(env->map);
	free(env->mlx);
	free(env);
	exit(0);
}

void	hook_controls(t_fdf *env)
{
	mlx_hook(env->win, 2, 0, key_press, env);
	mlx_hook(env->win, 4, 0, mouse_down, env);
	mlx_hook(env->win, 5, 0, mouse_up, env);
	mlx_hook(env->win, 6, 0, mouse_move, env);
	mlx_hook(env->win, 17, 0, close_win, env);
}

double	reset_angles(double angle)
{
	if (angle >= M_PI)
		return (-2 * M_PI - angle);
	else if (angle <= -M_PI)
		return (2 * M_PI + angle);
	return (angle);
}
