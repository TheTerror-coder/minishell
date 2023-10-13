# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 21:29:59 by TheTerror         #+#    #+#              #
#    Updated: 2023/10/12 20:00:58 by TheTerror        ###   ########lyon.fr    #
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
ENVTOOLS_PATH = ./envtools/
PIPEX_PATH = ./pipex/
COMMANDTOOLS_PATH = ./commandtools/

INCLUDE = minishell.h preminishell.h $(PIPEX_PATH)pipex.h $(PIPEX_PATH)prepipex.h


CC = 				cc
CFLAGS=				-Wall -Werror -Wextra	
RM =				rm -rf

SRC_BUILTINS = $(addprefix $(BUILTINS_PATH), unset.c export.c echo.c cd.c cd_options.c pwd.c env.c)
SRC_MEMTOOLS = $(addprefix $(MEMTOOLS_PATH), initmem.c freemem.c)
SRC_UTILS = $(addprefix $(UTILS_PATH), utils1.c tmpfile.c)
SRC_PARSING = $(addprefix $(PARSING_PATH), parseline1.c parseline2.c parseargv1.c setpipeline.c)
SRC_LAUNCHING = $(addprefix $(LAUNCHING_PATH), launcher.c executable.c)
SRC_PATHTOOLS = $(addprefix $(PATHTOOLS_PATH), setcmdpath.c getvalidpaths.c utils.c)
SRC_ENVTOOLS = $(addprefix $(ENVTOOLS_PATH), setenv.c env_utils.c)
SRC_REDIR_TOOLS = $(addprefix $(REDIR_TOOLS_PATH), redirections.c ioredir.c heredoc.c)
SRC_PIPEX =	$(addprefix $(PIPEX_PATH), pipex.c) \
			$(addprefix $(PIPEX_PATH)/utils/, utils1.c utils2.c) \
			$(addprefix $(PIPEX_PATH)/fpipetools/, plumber.c pathutils.c pathutils2.c iosetter.c) \
			$(addprefix $(PIPEX_PATH)/memorytools/, initmem.c freemem.c closer.c) \
			$(addprefix $(PIPEX_PATH)/bonus/, bonus.c)
SRC_COMMAND_TOOLS =	$(addprefix $(COMMANDTOOLS_PATH), create_commands.c command_args.c get_word.c get_redirection.c get_outfile_redir.c get_outfile_append_redir.c get_infile_redir.c get_heredoc.c get_pipe.c commands_utils.c commands.c tokens.c)
SRC = 	main.c minishell.c $(SRC_MEMTOOLS) $(SRC_UTILS) \
		$(SRC_LAUNCHING) $(SRC_PATHTOOLS) $(SRC_REDIR_TOOLS) $(SRC_BUILTINS) \
		$(SRC_ENVTOOLS) $(SRC_COMMAND_TOOLS)

OBJ := $(SRC:%.c=%.o)

%.o : %.c $(INCLUDE) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -c $< -o $@


all : make_libft $(NAME)

$(NAME) : $(OBJ)
	$(CC) -lbsd $(CFLAGS) $(OBJ) $(LIBFT_LIB) -I. -lreadline -o $@

make_libft :
	make -C $(LIBFT_PATH)

clean :
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJ)
fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME)
re : fclean all
