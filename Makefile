# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 21:29:59 by TheTerror         #+#    #+#              #
#    Updated: 2023/07/22 03:23:27 by lmohin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT_LIB = $(LIBFT_PATH)/libft.a

LIBFT_PATH = ./libft/
OBJECTS_PATH = ./objects/
MEMTOOLS_PATH = ./memtools/
UTILS_PATH = ./utils/
PARSING_PATH = ./parsing/
LAUNCHING_PATH = ./launching/
PATHTOOLS_PATH = ./pathtools/
REDIR_TOOLS_PATH = ./redir_tools/
BUILTINS_PATH = ./builtins/

INCLUDE = minishell.h preprocss.h


CC = 				cc
CFLAGS=				-Wall -Werror -Wextra
RM =				rm -rf

SRC_BUILTINS = $(addprefix $(BUILTINS_PATH), echo.c)
SRC_MEMTOOLS = $(addprefix $(MEMTOOLS_PATH), initmem.c freemem.c)
SRC_UTILS = $(addprefix $(UTILS_PATH), checking.c utils1.c)
SRC_PARSING = $(addprefix $(PARSING_PATH), parseline1.c parseline2.c parseargv1.c)
SRC_LAUNCHING = $(addprefix $(LAUNCHING_PATH), launcher.c executable.c)
SRC_PATHTOOLS = $(addprefix $(PATHTOOLS_PATH), setcmdpath.c getvalidpaths.c utils.c)
SRC_REDIR_TOOLS = $(addprefix $(REDIR_TOOLS_PATH), ioredir.c heredoc.c)
SRC = 	main.c minishell.c $(SRC_MEMTOOLS) $(SRC_PARSING) $(SRC_UTILS) \
		$(SRC_LAUNCHING) $(SRC_PATHTOOLS) $(SRC_REDIR_TOOLS) $(SRC_BUILTINS)

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
