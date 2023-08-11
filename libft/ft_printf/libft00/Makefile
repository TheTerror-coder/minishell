# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/10 15:29:29 by TheTerror         #+#    #+#              #
#    Updated: 2023/05/08 20:14:13 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

HEADER = 	libft00.h
NAME = 		libft00.a
CFLAGS = 	-Wall -Werror -Wextra
CC = 		cc
AR = 		ar -rc

SRC = 		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c\
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c\
			ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c\
			ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c\
			ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
			ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
			ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
			ft_lstmap.c
			
OBJ = 		$(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c -o $@ $<

bonus : $(OBJ_BONUS) $(HEADER)
	@$(AR) $(NAME) $^
	@ranlib $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	@$(AR) $@ $^
	@ranlib $(NAME)

clean :
	@$(RM) $(OBJ) $(OBJ_BONUS)
fclean : clean
	@$(RM) $(NAME)
re : fclean all