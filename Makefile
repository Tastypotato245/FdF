# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyusulee <kyusulee@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/09 14:38:00 by kyusulee          #+#    #+#              #
#    Updated: 2024/01/26 13:03:48 by kyusulee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf

HEAD		=	$(INCL_DIR)fdf.h
HEAD_B		=	$(INCL_DIR)fdf_bonus.h

SRCS		=	$(SRCS_DIR)fdf.c		\
				$(SRCS_DIR)parse.c		\
				$(SRCS_DIR)mouse.c		\
				$(SRCS_DIR)keyboard.c	\
				$(SRCS_DIR)control.c	\
				$(SRCS_DIR)color.c		\
				$(SRCS_DIR)draw.c		\
				$(SRCS_DIR)bresenham.c	\
				$(SRCS_DIR)project.c	\
				$(SRCS_DIR)utils.c

SRCS_B		=	$(SRCS_B_DIR)fdf_bonus.c		\
				$(SRCS_B_DIR)parse_bonus.c		\
				$(SRCS_B_DIR)mouse_bonus.c		\
				$(SRCS_B_DIR)keyboard_bonus.c	\
				$(SRCS_B_DIR)control_bonus.c	\
				$(SRCS_B_DIR)color_bonus.c		\
				$(SRCS_B_DIR)draw_bonus.c		\
				$(SRCS_B_DIR)bresenham_bonus.c	\
				$(SRCS_B_DIR)project_bonus.c	\
				$(SRCS_B_DIR)utils_bonus.c

OBJS		=	$(SRCS:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)

KYUSULIB	=	./kyusulib/
KYUSULIB_A	=	$(addprefix $(GNL), kyusulib.a)

SRCS_DIR	=	./srcs/
SRCS_B_DIR	=	./srcs_bonus/
INCL_DIR	=	./includes/

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
ECHO		=	echo

ifdef WITH_BONUS
    OBJS_SWITCH = $(OBJS_B)
	HEAD_SWITCH = $(HEAD_B)
else
    OBJS_SWITCH = $(OBJS)
	HEAD_SWITCH = $(HEAD)
endif

all			:
				@$(MAKE) $(NAME)
				@$(ECHO) "*** Make <fdf> complete."

bonus		:	
				@$(MAKE) WITH_BONUS=1 $(NAME)
				@$(ECHO) "*** Make <fdf> complete. (BONUS)"

$(NAME)		:	$(OBJS_SWITCH) $(HEAD_SWITCH)
				@$(MAKE) -C $(KYUSULIB)
				@$(CC) $(CFLAGS) -I$(INCL_DIR) $(OBJS_SWITCH) -L$(KYUSULIB) -lkyusulib -lmlx -lm -framework OpenGL -framework AppKit -o $(NAME)
				@$(ECHO) "*** Linking complete."

clean		:
				@$(MAKE) clean -C $(KYUSULIB)
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_B)
				@$(ECHO) "*** Clean <fdf>."

fclean		:
				@$(MAKE) fclean -C $(KYUSULIB)
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_B)
				@$(RM) $(NAME)
				@$(ECHO) "*** Fclean <fdf>."

re			:
				@$(ECHO) "*** Re-make <fdf> start."
				@$(MAKE) fclean
				@$(MAKE) all
				@$(ECHO) "*** Re-make <fdf> complete."

%.o			:	%.c
				@$(CC) $(CFLAGS) -I$(INCL_DIR) -c $^ -o $@

.PHONY		:	all clean fclean re bonus
