/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:24:52 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/15 17:42:58 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static int	val_in_base(const char c, const char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		++i;
	}
	return (-1);
}

static int	base_checker(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0' || str[1] == '\0')
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+')
			return (1);
		if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			return (1);
		if (ft_strchr(&str[i + 1], str[i]) != NULL)
			return (1);
		++i;
	}
	return (0);
}

unsigned int	ft_atoi_base(const char *str, const char *base)
{
	int				val;
	unsigned int	res;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	res = 0;
	len = ft_strlen(base);
	if (!base_checker(base))
		return (0);
	while ((str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		++i;
	if (ft_strncmp(&str[i], "0x", 2) == 0
			&& ft_strncmp(base, "0123456789ABCDEF", 16) == 0)
		i += 2;
	while (str[i])
	{
		val = val_in_base(ft_toupper(str[i]), base);
		if (val == -1)
			break;
		res = (res * len) + val_in_base(ft_toupper(str[i]), base);
		++i;
	}
	return (res);
}
