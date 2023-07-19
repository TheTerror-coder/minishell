# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 16:31:51 by TheTerror         #+#    #+#              #
#    Updated: 2023/05/10 21:28:55 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = ../pipex
LIBFTLIB = $(LIBFT_PATH)libft.a

PIPEX_PATH = ../
LIBFT_PATH = ../include/libft/
UTILS_PATH = ../utils/
FPIPETOOLS_PATH = ../fpipetools/
MEMORYTOOLS_PATH = ../memorytools/

INCLUDE_BONUS = $(PIPEX_PATH)ft_pipex.h $(PIPEX_PATH)ft_preprocss.h $(LIBFT_PATH)libft.h $(UTILS_PATH)ft_utils.h\
			$(FPIPETOOLS_PATH)ft_pipetools.h $(MEMORYTOOLS_PATH)ft_memtools.h ft_bonus.h

CFLAGS = 	-Wall -Werror -Wextra
CC = 		cc

SRC_UTILS = $(addprefix $(UTILS_PATH), ft_utils1.c ft_utils2.c)
SRC_FPIPETOOLS = $(addprefix $(FPIPETOOLS_PATH), ft_plumber.c ft_pathutils1.c ft_pathutils2.c ft_iosetter.c)
SRC_MEMORYTOOLS = $(addprefix $(MEMORYTOOLS_PATH), ft_initmem.c ft_freemem.c ft_closer.c)
SRC_BONUS = ft_bonus.c ft_heredoc.c $(PIPEX_PATH)ft_pipex.c $(SRC_UTILS) $(SRC_FPIPETOOLS) $(SRC_MEMORYTOOLS)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : make_libft $(NAME)

%.o : %.c $(INCLUDE_BONUS) $(LIBFTLIB)
	$(CC) $(CFLAGS) -c -o $@ $<

make_libft:
	make -C $(LIBFT_PATH)

$(NAME) : $(OBJ_BONUS) $(INCLUDE_BONUS)
	$(CC) $(CFLAGS) $^ $(LIBFTLIB) -o $@

clean :
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJ_BONUS)
fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME)
re : fclean all