# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/20 18:02:59 by TheTerror         #+#    #+#              #
#    Updated: 2023/08/11 12:16:34 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

LIBFT_PATH = ./libft00/
SRCS_PATH = ./srcs/
UTILS_PATH = ./utils/
BONUS_PATH = ./bonus/

INCLUDE =  ft_printf.h ft_local.h ft_preprcss.h libft00/libft00.h $(SRCS_PATH)ft_srcs.h

LIBFT00_A =	libft00.a
NAME 	=	libftprintf.a

CFLAGS	=	-Wall -Werror -Wextra
CC 		=	cc
AR		=	ar -rc

SRC =	ft_printf.c \
		$(addprefix $(SRCS_PATH), ft_hexa_base.c ft_islowcase.c \
		ft_print_char.c ft_isupcase.c ft_print_adr.c ft_print_hex.c \
		ft_print_int.c ft_print_unsign.c ft_print_str.c) \
		$(addprefix $(UTILS_PATH), ft_utils1.c ft_utils2.c ft_utils3.c) \
		$(addprefix $(BONUS_PATH), ft_put_spaces.c ft_put_zeros.c ft_sw_optionals.c)
OBJ =	$(SRC:.c=.o)

all : make_libft $(NAME)

%.o : %.c $(INCLUDE) $(LIBFT_PATH)$(LIBFT00_A)
	@$(CC) $(CFLAGS) -c -o $@ $<

make_libft :
	@make -C $(LIBFT_PATH)

bonus : $(OBJ) $(INCLUDE)

$(NAME) : $(OBJ) $(INCLUDE)
	@cp $(LIBFT_PATH)$(LIBFT00_A) .
	@mv $(LIBFT00_A) $(NAME)
	$(AR) $@ $^
	@ranlib $(NAME)

clean :
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJ)
fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME)
re : fclean all