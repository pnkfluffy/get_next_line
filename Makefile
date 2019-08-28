# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jfelty <jfelty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/20 16:57:41 by jfelty            #+#    #+#              #
#    Updated: 2019/08/27 17:38:27 by jfelty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = gnl

CC = @gcc

CFLAGS = -Wall -Wextra -Werror -g

SRC = get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): lib out

lib:
	@make -C libft
	@cp libft/libft.a .
	@echo "library copy generated"

out:
	@$(CC) $(CFLAGS) $(SRC) libft.a -o gnl
	@echo "gnl generated"

clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean

fclean: clean
	@rm -f $(NAME)
	@rm -f libft.a
	@make -C libft/ fclean

re: fclean all

.PHONY: lib out clean all fclean re gnl