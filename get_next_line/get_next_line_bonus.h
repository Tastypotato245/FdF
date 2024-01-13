/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyusulee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:23:00 by kyusulee          #+#    #+#             */
/*   Updated: 2023/11/18 16:57:00 by kyusulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_lst
{
	int				fd;
	char			*str;
	size_t			bgn;
	size_t			end;
	size_t			len;
	size_t			cap;
	struct s_lst	*next;
}				t_lst;

int		ft_lstnewadd_front(t_lst **lst, int fd);
t_lst	*ft_lstfind_lst(t_lst *lst, int fd);
int		ft_lstcap_change(t_lst *lst, size_t new_cap);
void	*ft_lstdel_one(t_lst **lst, int fd);
int		ft_lstappend_str(t_lst *lst, char *buf, size_t len);
int		ft_lstset_end(t_lst *lst);
char	*make_str_from_lst(t_lst **lst, t_lst *now);
char	*read_str_from_fd(t_lst **lst, t_lst *now);
char	*get_next_line(int fd);

#endif
