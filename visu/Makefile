# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcharbon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/21 11:21:25 by lcharbon          #+#    #+#              #
#    Updated: 2017/10/13 06:50:13 by lcharbon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = visual_filler.bin

CC = gcc
FLAG = -g
#FLAG = -Wall -Werror -Wextra

SRC_P = ./src/
OBJ_P = ./obj/
INC_P = ./include/
LIB_P = ./libft/

SRC_N = visual_filler.c

OBJ_N = $(SRC_N:.c=.o)
LIB_N = libft/libft.a

SRC = $(addprefix $(SRC_P),$(SRC_N))
OBJ = $(addprefix $(OBJ_P),$(OBJ_N))
INC = $(addprefix -I,$(INC_P))

all : lib
	@make $(NAME)

$(NAME) : $(OBJ)
	@$(CC) lib/libft.a lib/libmlx.a -framework OpenGL -framework AppKit $^ -o $@
	@echo
	@echo "\x1b[33mCompilation.... $(NAME) |\x1b[32m| done\x1b[37m"

$(OBJ_P)%.o: $(SRC_P)%.c $(INCLUDE)
	@mkdir -p $(OBJ_P)
	@$(CC) $(FLAG) $(INC) -o $@ -c $<
	@echo "\x1b[33mCompilation.... $@ $< |\x1b[32m| done\x1b[37m"

clean:
	@rm -rf $(OBJ) $(OBJ_P)

uclean : 
	@rm -rf $(OBJ) $(OBJ_P)

fclean: clean
	@rm -f $(NAME)

re : fclean all

ure : uclean all
