# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 14:38:00 by kyusulee          #+#    #+#              #
#    Updated: 2024/01/13 20:58:05 by kyusulee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

SRCS		=	fdf.c	\
OBJS		=	$(SRCS:.c=.o)

LIBFT		=	libft/
GNL			=	get_next_line/
MLX			=	minilibx/
LIBFT_A		=	$(addprefix $(LIBFT), libft.a)
GNL_A		=	$(addprefix $(GNL), libgnl.a)
MLX_A		=	$(addprefix $(MLX), libmlx.a)

SRCS_DIR	=	./srcs/
INCL_DIR	=	./includes/

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
ECHO		=	echo

all			:	$(NAME)
				@$(ECHO) "*** Make <fdf> complete."

bonus		:	$(NAME)
				@$(ECHO) "*** Make <fdf> complete. (BONUS)"

$(NAME)		:	$(OBJS) $(LIBFT_A) $(GNL_A) $(PRINTF_A)
				@$(CC) $(CFLAGS) -I$(INCL_DIR) $(OBJS) -L$(LIBFT) -lft -L$(GNL) -lgnl -L$(MLX) -lmlx -lm -o $(NAME) -framework OpenGL -framework AppKit
				@$(ECHO) "*** Linking complete."

$(LIBFT_A):
				@$(MAKE) -s -C $(LIBFT)
				@echo "Compiled $(LIBFT_A)."

$(GNL_A):
				@$(MAKE) -s -C $(GNL)
				@echo "Compiled $(GNL_A)."

$(MLX_A):
				@$(MAKE) -s -C $(MLX)
				@echo "Compiled $(MLX_A)."

clean		:
				@$(RM) $(OBJS)
				@$(MAKE) clean -C $(LIBFT)
				@$(MAKE) clean -C $(GNL)
				@$(MAKE) clean -C $(MLX)
				@$(ECHO) "*** Clean <fdf>."

fclean		:
				@$(MAKE) clean -C $(LIBFT)
				@$(MAKE) -C $(LIBFT) fclean
				@$(MAKE) -C $(GNL) fclean
				@$(MAKE) -C $(MLX) clean
				@$(RM) $(NAME)
				@$(RM) $(OBJS)
				@$(ECHO) "*** Fclean <fdf>."

re			:
				@$(ECHO) "*** Re-make <pipex> start."
				@$(MAKE) fclean
				@$(MAKE) all
				@$(ECHO) "*** Re-make <pipex> complete."

.PHONY		:	all clean fclean re bonus
