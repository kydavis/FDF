# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 18:48:35 by kdavis            #+#    #+#              #
#    Updated: 2017/01/05 16:04:22 by kdavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

MAKE		= make

FILENAMES	= main.c fdf_error.c fdf_initalize.c fdf_pixel.c fdf_map_reader.c
FILENAMES	+=fdf_sinlookup.c fdf_matrix.c fdf_transform.c #test_mallocwrap.c

L1			= ft
L2			= mlx

SRCDIR		= src/
IDIR		= includes/
LIBDIR		= lib/

SRC			=$(addprefix $(SRCDIR), $(FILENAMES))
LIB1		=$(addprefix lib, $(L1))
LIB2		=$(addprefix lib, $(L2))

IFLAGS		=-I $(IDIR) -I $(LIBDIR)$(L1)/$(IDIR) -I $(LIBDIR)$(L2)/
CFLAGS		= -Wall -Werror -Wextra -framework OpenGL -framework AppKit #-fsanitize=address
LFLAGS		= -L $(LIBDIR) -l$(L1) -l$(L2)
CC			= gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): | $(LIBDIR)$(LIB1).a $(LIBDIR)$(LIB2).a
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(SRC) -o $@

$(LIBDIR)$(LIB1).a:
	$(MAKE) -C $(LIBDIR)$(L1)
	cp -rf $(LIBDIR)$(L1)/$(LIB1).a $(LIBDIR)$(LIB1).a

$(LIBDIR)$(LIB2).a:
	$(MAKE) -C $(LIBDIR)$(L2)
	cp -rf $(LIBDIR)$(L2)/$(LIB2).a $(LIBDIR)$(LIB2).a

clean:
	$(MAKE) -C $(LIBDIR)$(L1) clean
	$(MAKE) -C $(LIBDIR)$(L2) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBDIR)lib$(L1).a
	rm -rf $(LIBDIR)lib$(L2).a
	$(MAKE) -C $(LIBDIR)$(L1) fclean

.PHONY: eclean
eclean:
	rm -rf $(NAME)

re: fclean all

.PHONY: ere
ere: eclean all
