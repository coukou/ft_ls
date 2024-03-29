# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 16:54:27 by spopieul          #+#    #+#              #
#    Updated: 2018/03/08 19:44:12 by orenkay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = gcc
CFLAGS = -Wall -Wextra # -Werror

INC = -I includes/ -I libft/includes

SRCS_DIR = srcs
OBJS_DIR = objs

OBJS_FILES = \
	main.o parse.o utils.o entry.o entry2.o \
	entry3.o sort.o sort2.o color.o print.o \
	format.o

OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

LIBFT_MAKE = @make -s -C libft
LIBFT = libft/libft.a

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(INC) $(CFLAGS) -o $@ $<

$(NAME): $(OBJS)
	$(LIBFT_MAKE)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

clean:
	@/bin/rm -rf $(OBJS)
	$(LIBFT_MAKE) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	$(LIBFT_MAKE) fclean

re: fclean all
