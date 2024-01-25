/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:36:58 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/25 21:44:27 by kyusulee         ###   ########.fr       */
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

// steep 0 < n <= 1
static void	bresenham_0(t_point s, t_point e, t_fdf *env, t_point dir)
{
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
	while (m.x != e.x + dir.x)
	{
		put_pixel(env, m.x, m.y, get_color(e));
		if (f < 0)
			f += df1;
		else
		{
			m.y += dir.y;
			f += df2;
		}
		m.x += dir.x;
	}
}

// steep n > 1
static void	bresenham_1(t_point s, t_point e, t_fdf *env, t_point dir)
{
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
	while (m.y != e.y + dir.y)
	{
		put_pixel(env, m.x, m.y, get_color(e));
		if (f < 0)
			f += df1;
		else
		{
			m.x += dir.x;
			f += df2;
		}
		m.y += dir.y;
	}
}

void	draw_line(t_point s, t_point e, t_fdf *env)
{
	t_point	d;
	t_point	dir;

	d.y = ft_abs(e.y - s.y);
	d.x = ft_abs(e.x - s.x);
	dir.x = -2 * (s.x > e.x) + 1;
	dir.y = -2 * (s.y > e.y) + 1;
	if (d.x == 0 || d.y / d.x >= 1)
		bresenham_1(s, e, env, dir);
	else
		bresenham_0(s, e, env, dir);
}
