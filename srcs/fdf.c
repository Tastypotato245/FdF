/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:28:38 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/25 22:44:17 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static t_fdf	*ft_init(const char *path)
{
	t_fdf	*env;
	char	*title;

	title = ft_strjoin("FdF - ", path);
	env = (t_fdf *)null_guard(malloc(sizeof(t_fdf)));
	env->mlx = mlx_init();
	env->win = null_guard(mlx_new_window(env->mlx, WIDTH, HEIGHT, title));
	free(title);
	env->map = NULL;
	env->img = NULL;
	env->data_addr = NULL;
	env->camera = NULL;
	env->mouse = (t_mouse *)null_guard(malloc(sizeof(t_mouse)));
	return (env);
}

static t_map	*map_init(void)
{
	t_map	*map;

	map = (t_map *)null_guard(malloc(sizeof(t_map)));
	map->height = 0;
	map->width = 0;
	map->array = NULL;
	return (map);
}

static t_camera	*camera_init(t_fdf *env)
{
	t_camera	*camera;

	camera = (t_camera *)null_guard(malloc(sizeof(t_camera)));
	camera->zoom = ft_min(WIDTH / env->map->width / 2,
			HEIGHT / env->map->height / 2);
	camera->x_angle = -0.523599;
	camera->y_angle = -0.523599;
	camera->z_angle = 0.615472;
	camera->z_height = 2;
	camera->x_offset = 0;
	camera->y_offset = 0;
	camera->iso = 1;
	return (camera);
}

int	main(int argc, char **argv)
{
	t_fdf	*env;

	if (argc != 2)
		exit_handler(0, "fdf", "./fdf <file.fdf>");
	env = ft_init(argv[1]);
	env->map = map_init();
	arg_checker(argv[1], env->map);
	env->camera = camera_init(env);
	hook_controls(env);
	drawer(env->map, env);
	mlx_loop(env->mlx);
	exit (0);
}
