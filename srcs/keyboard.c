/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:55:10 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/25 21:45:35 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void	reset(t_fdf *env)
{
	env->camera->x_offset = 0;
	env->camera->y_offset = 0;
	if (env->camera->iso)
	{
		env->camera->x_angle = -0.523599;
		env->camera->y_angle = -0.523599;
		env->camera->z_angle = 0.615472;
	}
	else
	{
		env->camera->x_angle = -0.523599;
		env->camera->y_angle = -0.261799;
		env->camera->z_angle = 0;
	}
	env->camera->z_height = 2;
	env->camera->zoom = ft_min(WIDTH / env->map->width / 2,
			HEIGHT / env->map->height / 2);
}

static void	toggle_projection(t_fdf *env)
{
	if (env->camera->iso)
	{
		env->camera->x_angle = -0.523599;
		env->camera->y_angle = -0.261799;
		env->camera->z_angle = 0;
	}
	else
	{
		env->camera->x_angle = -0.523599;
		env->camera->y_angle = -0.523599;
		env->camera->z_angle = 0.615472;
	}
	env->camera->iso = !env->camera->iso;
}

static void	mod_height(int keycode, t_fdf *env)
{
	if (keycode == MINUS)
		env->camera->z_height += 0.1;
	else if (keycode == PLUS)
		env->camera->z_height -= 0.1;
	if (env->camera->z_height < 0.1)
		env->camera->z_height = 0.1;
	else if (env->camera->z_height > 10)
		env->camera->z_height = 10;
}

static void	translate(int keycode, t_fdf *env)
{
	if (keycode == ARROW_LEFT)
		env->camera->x_offset -= 10;
	else if (keycode == ARROW_RIGHT)
		env->camera->x_offset += 10;
	else if (keycode == ARROW_DOWN)
		env->camera->y_offset += 10;
	else if (keycode == ARROW_UP)
		env->camera->y_offset -= 10;
}

int	key_press(int keycode, void *params)
{
	t_fdf	*env;

	env = (t_fdf *)params;
	if (keycode == ARROW_DOWN || keycode == ARROW_LEFT || keycode == ARROW_UP \
			|| keycode == ARROW_RIGHT)
		translate(keycode, env);
	else if (keycode == MINUS || keycode == PLUS)
		mod_height(keycode, env);
	else if (keycode == SPACE)
		toggle_projection(env);
	else if (keycode == KEY_R)
		reset(env);
	else if (keycode == ESCAPE)
		close_win(env);
	drawer(env->map, env);
	return (0);
}
