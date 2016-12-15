# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kdavis <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/13 10:16:17 by kdavis            #+#    #+#              #
#    Updated: 2016/12/14 16:57:45 by kdavis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= fdf

MAKE		= make

FILENAMES	= main.c

#LIBNAMES	= ft mlx
#LIB		= $(addprefix $(LIBDIR), $(LIBNAMES))

INCDIR		= includes/
LIBDIR		= lib/
BUILDIR		= build/
SRCDIR		= src/
LIBFT		= $(LIBDIR)ft/
LIBMLX		= $(LIBDIR)mlx/
SRC			= $(addprefix $(SRCDIR), $(FILENAMES))
BUILD		= $(addprefix $(BUILDIR), $(FILENAMES:.c=.o))
IFLAGS		= -I $(INCDIR) -I $(LIBFT)$(INCDIR) -I $(LIBMLX)
CFLAGS		= -Wall -Werror -Wextra $(IFLAGS) -L $(LIBDIR) -lft -lmlx
CC			= gcc

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -rf $(BUILDIR)
	$(MAKE) -C $(LIBFT) clean
	$(MAKE) -C $(LIBMLX) clean

.PHONY: fclean
fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(LIBMLX) clean

.PHONY: re
re: fclean all

$(NAME): $(SRC) | $(BUILD)
	$(CC) $(CFLAGS) $(BUILD) -o $@

$(BUILDIR)%.o: $(SRCDIR)%.c | build lib
	$(CC) $(CFLAGS) -c $^ -o $@

build:
	mkdir $(BUILDIR)

lib:
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(LIBMLX)
	cp $(LIBFT)/libft.a $(LIBDIR)
	cp $(LIBFT)/libmlx.a $(LIBDIR)
