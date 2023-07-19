# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 16:50:43 by TheTerror         #+#    #+#              #
#    Updated: 2023/05/10 21:27:59 by TheTerror        ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFTLIB = $(LIBFT_PATH)libft.a

LIBFT_PATH = ./include/libft/
UTILS_PATH = ./utils/
FPIPETOOLS_PATH = ./fpipetools/
MEMORYTOOLS_PATH = ./memorytools/
BONUS_PATH = ./bonus/


INCLUDE = ft_pipex.h ft_preprocss.h $(LIBFT_PATH)libft.h $(UTILS_PATH)ft_utils.h\
			$(FPIPETOOLS_PATH)ft_pipetools.h $(MEMORYTOOLS_PATH)ft_memtools.h


CFLAGS = 	-Wall -Werror -Wextra
CC = 		cc
AR = 		ar -rc

SRC_UTILS = $(addprefix $(UTILS_PATH), ft_utils1.c ft_utils2.c)
SRC_ONLY_MANDATORY = $(addprefix $(UTILS_PATH), ft_utils3.c)
SRC_FPIPETOOLS = $(addprefix $(FPIPETOOLS_PATH), ft_plumber.c ft_pathutils1.c ft_pathutils2.c ft_iosetter.c)
SRC_MEMORYTOOLS = $(addprefix $(MEMORYTOOLS_PATH), ft_initmem.c ft_freemem.c ft_closer.c)
SRC = ft_pipex.c $(SRC_UTILS) $(SRC_FPIPETOOLS) $(SRC_MEMORYTOOLS) $(SRC_ONLY_MANDATORY)

OBJ = $(SRC:.c=.o)
BONUS_O = $(addprefix $(BONUS_PATH), ft_bonus.o ft_heredoc.o)

all : make_libft rm_bonus $(NAME)

%.o : %.c $(INCLUDE) $(LIBFTLIB)
	$(CC) $(CFLAGS) -c -o $@ $<

make_libft:
	make -C $(LIBFT_PATH)

$(NAME) : $(OBJ) $(INCLUDE)
	$(CC) $(CFLAGS) $^ $(LIBFTLIB) -o $@

bonus : make_bonus

make_bonus :
	make -C $(BONUS_PATH)

rm_bonus :
	@$(RM) $(BONUS_O)
clean :
	@make clean -C $(LIBFT_PATH)
	@make clean -C $(BONUS_PATH)
	@$(RM) $(OBJ)
fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@make fclean -C $(BONUS_PATH)
	@$(RM) $(NAME)
re : fclean all