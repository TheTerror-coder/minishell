/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:04:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/18 14:26:07 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREMINISHELL_H
# define PREMINISHELL_H

#include "libft/libft.h"

# define __SKIP 2
# define __WHANG 0
# define __PRINT PRINT_ERROR
# define __PERROR PUT_ERROR
# define __CLOSED_FD -111 // arbitrary negative number to initialize a file descriptor variable
# define __FTEMP_LIMITS 9999999 // number of possible names of the temporary file
# define __EXIT_REACHED 7
# define __RADICAL "/tmp/ueyjq7ZbZhs26jd"
# define __FALLOC "failed allocation"
# define __SERROR "syntax error near unexpected token `newline'"

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
	char		*pathcmd;
	char		**paths;
	char		*str;
	char		*set;
	int			status;
	int			i;
	int			d;
	int			jx;
	int			nbcmd;
	int			infile_fd;
	int			outfile_fd;
	int			sp[2];
	int			**p;
	int			stdin;
	int			stdout;
	int			pipe_outfd;
	int			*pid;
	int			exit;
	t_bool		skip_command_flg;
	t_commands	*commands;
	t_commands	*iterator;
}				t_ppex;

typedef struct s_vars
{
	t_env	*my_env;
	t_commands *commands;
	char	*pwd;
	char	**envp;
	char	*line;
	char	**paths;
	char	*str;
	char	*set;
	char	**argv;
	char	*cmdpath;
	char	*limiter;
	char	*ftemp1;
	int		status;
	int		exit_code;
	int		p1[2];
	int		p2[2];
	int		jx;
	int		nb;
	int		infd;
	int		outfd;
	int		hdoc_fd;
	t_bool	flg_expand_in_hdoc;
	t_ppex	*var;
}				t_vars;
#endif
