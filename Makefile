# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: orenkay <orenkay@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/21 16:54:27 by spopieul          #+#    #+#              #
#    Updated: 2018/02/23 12:00:19 by orenkay          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# LIBFT
# ----------

LIBS_DIR += libft
INC += -I libft/includes
LIBS += libft/libft.a

# FT_PRINTF
# ----------

LIBS_DIR += ft_printf
INC += -I ft_printf/includes
LIBS += ft_printf/libftprintf.a

# FT_LS
# ----------

NAME = ft_ls
CC = gcc
CFLAGS = #-Wall -Wextra -Werror

INC += -I includes/

SRCS_DIR = srcs
OBJS_DIR = objs

OBJS_FILES = main.o opts.o utils.o sort.o
OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS_FILES))

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(INC) $(CFLAGS) -o $@ $<

$(NAME): $(OBJS)
	@$(foreach lib, $(LIBS_DIR), make -C $(lib) > /dev/null;)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME) -lm

all: $(NAME)

clean:
	@/bin/rm -rf $(OBJS)
	# @$(foreach lib, $(LIBS_DIR), make -C $(lib) clean > /dev/null;)

fclean: clean
	@/bin/rm -rf $(NAME)
	# @$(foreach lib, $(LIBS_DIR), make -C $(lib) fclean > /dev/null;)

re: fclean all
