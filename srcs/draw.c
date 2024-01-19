/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:34:43 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/19 19:58:18 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

// little_endian
static void	put_pixel(t_fdf *env, int x, int y, int color)
{
	int		i;

	if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
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
		return (0x59A896);
	percent = ((double)(z - z_min) / max);
	if (percent < 0.2)
		return (0x59A896);
	else if (percent < 0.4)
		return (0x714674);
	else if (percent < 0.6)
		return (0x6CCCB6);
	else if (percent < 0.8)
		return (0x79E5CB);
	else
		return (0xFFFFFF);
}

static int	get_color(int z, int z_min, int z_max, int color)
{
	if (color == -1)
		return (get_default_color(z, z_min, z_max));
	return (color);
}

void	draw_y0_first(t_fdf *env, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			put_pixel(env, x * 10, y * 10, \
					get_color(map->array[y][x][0], map->z_min, \
						map->z_max, map->array[y][x][1]));
			++x;
		}
		++y;
	}
}

//void	draw_x0_first(t_fdf *env, t_map *map);
//void	draw_yn_first(t_fdf *env, t_map *map);
//void	draw_xn_first(t_fdf *env, t_map *map);

// draw switcher
void	drawer(t_fdf *env, t_map *map)
{	
	draw_y0_first(env, map);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
