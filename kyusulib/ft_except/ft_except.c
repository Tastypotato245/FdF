/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_except.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:38:34 by kyusulee          #+#    #+#             */
/*   Updated: 2024/01/15 14:07:25 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_except.h"

void	exit_handler(int case_num, char *program_name, char *object)
{
	if (program_name != NULL)
	{
		ft_putstr_fd(program_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (object != NULL)
	{
		ft_putstr_fd(object, 2);
		ft_putstr_fd(": ", 2);
	}
	if (case_num == 0)
	{
		ft_putstr_fd("parse error\n", 2);
		exit(1);
	}
	else if (case_num == 127)
		ft_putstr_fd("command not found\n", 2);
	else
		ft_putendl_fd(strerror(errno), 2);
	exit(case_num);
}

int	func_guard(int result)
{
	if (result == -1)
		exit_handler(1, NULL, NULL);
	return (result);
}

void	*null_guard(void *pointer)
{
	if (pointer == NULL)
		exit_handler(1, NULL, NULL);
	return (pointer);
}
