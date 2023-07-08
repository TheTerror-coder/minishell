# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 21:29:59 by TheTerror         #+#    #+#              #
#    Updated: 2023/07/08 18:16:39 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_LIB = $(LIBFT_PATH)/libft.a

LIBFT_PATH = ./libft/
OBJECTS_PATH = ./objects/
MEMTOOLS_PATH = ./memtools/
PARSING_PATH = ./memtools/

INCLUDE = minishell.h preprocss.h


CC = 				cc
CFLAGS=				-Wall -Werror -Wextra
RM =				rm -rf

SRC_MEMTOOLS = $(addprefix $(MEMTOOLS_PATH), initmem.c freemem.c)
SRC = minishell.c $(SRC_MEMTOOLS)

OBJ := $(SRC:%.c=%.o)

%.o : %.c $(INCLUDE) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -c $< -o $@


all : make_libft $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB)  -I. -lreadline -o $@

make_libft :
	make -C $(LIBFT_PATH)

clean :
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJ)
fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME)
re : fclean all