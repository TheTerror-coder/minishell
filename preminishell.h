/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:04:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/29 02:23:45 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREMINISHELL_H
# define PREMINISHELL_H

#include "libft/libft.h"

# define __SKIP 2
# define __CONTINUE 5
# define __WHANG 0
# define __PRINT PRINT_ERROR
# define __PERROR PUT_ERROR
# define __CLOSED_FD -111 // arbitrary negative number to initialize a file descriptor variable
# define __MAX_ATTEMPTS 9999999 // number of possible names of the temporary file
# define __EXIT_REACHED 7
# define __CMD_NOT_FOUND 127
# define __CMD_NOT_EXEC 126
# define __BUILTIN_ERROR 2
# define __RADICAL "/tmp/ueyjq7ZbZhs26jd56276HJZ"
# define __FALLOC "failed allocation"

extern int	exitstatus;

typedef enum e_typ
{
	PRINT_ERROR = 666,
	PUT_ERROR = 777
}				t_typ;

typedef struct s_env
{
	char		*var;
	struct	s_env 	*next;
}			t_env;

typedef struct s_token
{
	char		*content;
	int			type;
	int		expand_in_hdoc;
	struct s_token *next;
}			t_token;

typedef	struct s_commands
{
	char				*main_command;
	char				**arguments;
	int					hdoc_fd;
	struct s_token		*tokens;
	struct s_commands	*next;
}			t_commands;

typedef struct	s_ppex
{
	t_commands	*commands;
	t_commands	*iterator;
	char		*pathcmd;
	char		**paths;
	int			pipe_outfd;
	int			*pid;
	int			**p;
	int			status;
	int			i;
	int			nbcmd;
	t_bool		skip_command_flg;
}				t_ppex;

typedef struct s_vars
{
	t_env	*my_env;
	t_commands *commands;
	char	*cmdpath;
	char	*pwd;
	char	*line;
	char	**paths;
	char	*str;
	char	*ftemp1;
	char	*limiter;
	int		status;
	int		p1[2];
	int		p2[2];
	int		infd;
	int		outfd;
	int		stdin;
	int		stdout;
	int		hdoc_fd;
	t_bool	flg_var_is_null;
	t_bool	flg_parsing_is_ok;
	t_bool	flg_expand_in_hdoc;
	t_bool	flg_exit_main_procss;
	t_ppex	*var;
}				t_vars;
#endif
