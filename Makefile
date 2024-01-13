# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 14:38:00 by kyusulee          #+#    #+#              #
#    Updated: 2024/01/13 15:52:01 by kyusulee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

LIBFT		=	libft/
GNL			=	get_next_line/
MLX			=	minilibx/

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I$(INCLUDE)
RM			=	rm -f
SRCS		=	fdf.c
OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:


bonus		:	all

clean		:
				@$(RM) $(OBJS)
				@echo "Clean FdF."
				@$(MAKE) clean -s -C $(LIBFT)
				@echo "Clean libft."
				@$(MAKE) clean -s -C $(GNL)
				@echo "Clean gnl."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."

fclean		:
				@$(MAKE) clean -s
				@$(MAKE) fclean -s -C $(LIBFT)
				@echo "Full clean libft."
				@$(MAKE) fclean -s -C $(GNL)
				@echo "Full clean gnl."
				@$(MAKE) clean -s -C $(MLX)
				@echo "Clean mlx."
				@$(RM) $(NAME)
				@echo "Removed executable."

re			:
				@$(MAKE) fclean
				@$(MAKE) all

.PHONY		:	all clean fclean re bonus
