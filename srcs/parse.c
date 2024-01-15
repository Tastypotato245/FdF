/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:41:49 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/15 17:42:16 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int	get_width(char *line)
{
	int		width;
	char	**split_str;

	split_str = ft_split(line, ' ');
	width = 0;
	while (split_str[width])
		++width;
	free_strarr(split_str);
	return (width);
}

static void	get_map_siz(char *filename, int *w, int *h)
{
	int		fd;
	char	*line;

	*h = 0;
	fd = func_guard(open(filename, O_RDONLY));
	line = get_next_line(fd);
	if (line)
		*w = get_width(line);
	while (line)
	{
		++(*h);
		free(line);
		line = get_next_line(fd);
	}
	func_guard(close(fd));
	get_next_line(fd);
}

static void	set_line_data(int **n, char *line, int width)
{
	char	**num;
	int		i;
	int		j;

	num = ft_split(line, ' ');
	i = -1;
	while (num[++i] && i < width)
	{
		n[i] = null_guard(malloc(sizeof(int) * 2));
		n[i][0] = ft_atoi(num[i]);
		j = 0;
		while (num[i][j] && num[i][j] != ',')
			j++;
		if (num[i][j] == ',')
			n[i][1] = ft_atoi_base(&num[i][++j], "0123456789ABCDEF");
		else
			n[i][1] = -1;
	}
	free_strarr(num);
}

static void	set_z_min_max(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->z_min = map->array[0][0][0];
	map->z_max = map->array[0][0][0];
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->array[i][j][0] > map->z_max)
				map->z_max = map->array[i][j][0];
			if (map->array[i][j][0] < map->z_min)
				map->z_min = map->array[i][j][0];
			++j;
		}
		++i;
	}
}

void	arg_checker(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	get_map_siz(filename, &(map->width), &(map->height));
	fd = func_guard(open(filename, O_RDONLY));
	map->array = null_guard(malloc(sizeof(int **) * map->height));
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		map->array[i] = null_guard(malloc(sizeof(int *) * map->width));
		set_line_data(map->array[i], line, map->width);
		free(line);
		line = get_next_line(fd);
		++i;
	}
	set_z_min_max(map);
	func_guard(close(fd));
	get_next_line(fd);
}
