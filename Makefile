# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/14 18:48:35 by kdavis            #+#    #+#              #
#    Updated: 2016/12/14 19:16:31 by kdavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

MAKE		= make

FILENAMES	= main.c

L1			= ft
L2			= mlx

SRCDIR		= src/
IDIR		= includes/
LIBDIR		= lib/

SRC			=$(addprefix $(SRCDIR), $(FILENAMES))

IFLAGS		=-I $(IDIR) -I $(LIBDIR)$(L1)/$(IDIR) -I $(LIBDIR)$(L2)/
CFLAGS		= -Wall -Werror -Wextra
LFLAGS		= -L $(LIBDIR) -l$(L1) -l$(L2)
CC			= gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): | $(LIB)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(SRC) -o $@

lib:
	$(MAKE) -C $(LIBDIR)$(L1)
	$(MAKE) -C $(LIBDIR)$(L2)
	cp -rf $(LIBDIR)$(L1)/lib$(L1).a $(LIBDIR)lib$(L1).a
	cp -rf $(LIBDIR)$(L2)/lib$(L2).a $(LIBDIR)lib$(L2).a

clean:
	$(MAKE) -C $(LIBDIR)$(L1) clean
	$(MAKE) -C $(LIBDIR)$(L2) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBDIR)lib$(L1).a
	rm -rf $(LIBDIR)lib$(L2).a
	$(MAKE) -C $(LIBDIR)$(L1) fclean

re: fclean all
