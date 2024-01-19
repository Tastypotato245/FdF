# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 14:38:00 by kyusulee          #+#    #+#              #
#    Updated: 2024/01/19 20:01:53 by kyusulee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

SRCS		=	$(SRCS_DIR)fdf.c	\
				$(SRCS_DIR)parse.c	\
				$(SRCS_DIR)utils.c	\
				$(SRCS_DIR)control.c\
				$(SRCS_DIR)mouse.c	\
				$(SRCS_DIR)keyboard.c	\
				$(SRCS_DIR)draw.c

OBJS		=	$(SRCS:.c=.o)

KYUSULIB	=	./kyusulib/
KYUSULIB_A	=	$(addprefix $(GNL), kyusulib.a)

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

$(NAME)		:	$(OBJS)
				@$(MAKE) -C $(KYUSULIB)
				@$(CC) $(CFLAGS) -I$(INCL_DIR) $(OBJS) -L$(KYUSULIB) -lkyusulib -lmlx -lm -framework OpenGL -framework AppKit -o $(NAME)
				@$(ECHO) "*** Linking complete."

clean		:
				@$(MAKE) clean -C $(KYUSULIB)
				@$(RM) $(OBJS)
				@$(ECHO) "*** Clean <fdf>."

fclean		:
				@$(MAKE) fclean -C $(KYUSULIB)
				@$(RM) $(OBJS)
				@$(RM) $(NAME)
				@$(ECHO) "*** Fclean <fdf>."

re			:
				@$(ECHO) "*** Re-make <fdf> start."
				@$(MAKE) fclean
				@$(MAKE) all
				@$(ECHO) "*** Re-make <fdf> complete."

./srcs/%.o	:	./srcs/%.c
				@$(CC) $(CFLAGS) -I$(INCL_DIR) -c $^ -o $@

.PHONY		:	all clean fclean re bonus
