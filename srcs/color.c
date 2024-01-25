/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 21:35:18 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/25 21:40:45 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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

int	get_color(t_point e)
{
	int		r;
	int		g;
	int		b;

	r = (e.color >> 16) & 0xFF;
	g = (e.color >> 8) & 0xFF;
	b = e.color & 0xFF;
	return ((r << 16) | (g << 8) | b);
}

