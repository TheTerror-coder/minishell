# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/06 21:29:59 by TheTerror         #+#    #+#              #
#    Updated: 2023/10/31 15:45:21 by lmohin           ###   ########.fr        #
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
SIGNAL_PATH = ./signals/

INCLUDE = minishell.h preminishell.h $(PIPEX_PATH)pipex.h


CC = 				cc
CFLAGS=				-Wall -Werror -Wextra	
RM =				rm -rf

SRC_BUILTINS = $(addprefix $(BUILTINS_PATH), builtin.c exit.c unset.c export.c echo.c cd.c cd_options.c pwd.c env.c)
SRC_MEMTOOLS = $(addprefix $(MEMTOOLS_PATH), initmem.c freemem.c)
SRC_UTILS = $(addprefix $(UTILS_PATH), utils.c tmpfile.c)
SRC_PARSING = $(addprefix $(PARSING_PATH), parseline1.c parseline2.c parseargv1.c setpipeline.c)
SRC_LAUNCHING = $(addprefix $(LAUNCHING_PATH), launcher.c executable.c)
SRC_PATHTOOLS = $(addprefix $(PATHTOOLS_PATH), setcmdpath.c getvalidpaths.c utils.c)
SRC_ENVTOOLS = $(addprefix $(ENVTOOLS_PATH), setenv.c env_utils.c)
SRC_REDIR_TOOLS = $(addprefix $(REDIR_TOOLS_PATH), ioredir.c heredoc.c expand_in_hdoc.c)
SRC_PIPEX =	$(addprefix $(PIPEX_PATH), pipex.c) \
			$(addprefix $(PIPEX_PATH)/utils/, utils1.c utils2.c) \
			$(addprefix $(PIPEX_PATH)/fpipetools/, plumber.c iosetter.c) \
			$(addprefix $(PIPEX_PATH)/memorytools/, initmem.c freemem.c closer.c)
SRC_COMMAND_TOOLS =	$(addprefix $(COMMANDTOOLS_PATH), expand_parsing.c null_expand_test.c create_commands.c command_args.c get_word.c get_redirection.c get_outfile_redir.c get_outfile_append_redir.c get_infile_redir.c get_heredoc.c get_pipe.c commands_utils.c commands.c tokens.c)
SRC_SIGNALS =	$(addprefix $(SIGNAL_PATH), signals.c)
SRC = 	main.c minishell.c $(SRC_MEMTOOLS) $(SRC_UTILS) \
		$(SRC_LAUNCHING) $(SRC_PATHTOOLS) $(SRC_REDIR_TOOLS) $(SRC_BUILTINS) \
		$(SRC_ENVTOOLS) $(SRC_COMMAND_TOOLS) $(SRC_PIPEX) $(SRC_SIGNALS)

OBJ := $(SRC:%.c=%.o)

%.o : %.c $(INCLUDE) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -c $< -o $@


all : make_libft $(NAME)
c : all clean

$(NAME) : $(OBJ)
	$(CC) -lbsd $(CFLAGS) $(OBJ) $(LIBFT_LIB) -I. -lreadline -o $@

make_libft :
	make -C $(LIBFT_PATH)

leaks: all
	rm valgrind.txt
	echo "{" > valgrind_ignore_leaks.txt
	echo "leak readline" >> valgrind_ignore_leaks.txt
	echo "Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "..." >> valgrind_ignore_leaks.txt
	echo "fun:readline" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	echo "{" >> valgrind_ignore_leaks.txt
	echo "leak add_history" >> valgrind_ignore_leaks.txt
	echo "Memcheck:Leak" >> valgrind_ignore_leaks.txt
	echo "..." >> valgrind_ignore_leaks.txt
	echo "fun:add_history" >> valgrind_ignore_leaks.txt
	echo "}" >> valgrind_ignore_leaks.txt
	valgrind --suppressions=valgrind_ignore_leaks.txt --leak-check=full \
			--show-leak-kinds=all --track-fds=yes \
			--show-mismatched-frees=yes --read-var-info=yes \
			--log-file=valgrind.txt -s ./${NAME}

clean :
	@make clean -C $(LIBFT_PATH)
	@$(RM) $(OBJ)
fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME)
re : fclean all
