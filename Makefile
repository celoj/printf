# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcelojev <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 15:36:34 by dcelojev          #+#    #+#              #
#    Updated: 2019/07/09 15:02:56 by dcelojev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = libftprintf.a
LIB_INC_DIR = libft

SRC	= src/ft_printf.c					\
	  src/ft_printf2.c					\
	  src/memory_manager.c				\
	  src/flag_manager.c				\
	  src/flag_manager2.c				\
	  src/helper_functions.c			\
	  src/conversions/s.c				\
	  src/conversions/c.c				\
	  src/conversions/d.c				\
	  src/conversions/f.c				\
	  src/conversions/o.c				\
	  src/conversions/p.c				\
	  src/conversions/u.c				\
	  src/conversions/x.c				\
	  src/conversions/capital_c.c		\
	  src/conversions/capital_s.c		\
	  src/conversions/capital_x.c		\

OBJ = 	ft_printf.o						\
		ft_printf2.o					\
		memory_manager.o				\
		flag_manager.o					\
		flag_manager2.o					\
		helper_functions.o				\
		s.o								\
		c.o								\
		d.o								\
		f.o								\
		o.o								\
		p.o								\
		u.o								\
		x.o								\
		capital_c.o						\
		capital_s.o						\
		capital_x.o						\

all: $(NAME)

$(OBJ):
	gcc -I . -I $(LIB_INC_DIR) -c $(SRC) -Wall -Werror -Wextra

$(NAME): $(OBJ)
	make -C $(LIB_INC_DIR)
	cp libft/libft.a ./$(NAME)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f *.o
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
