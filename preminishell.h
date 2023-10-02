/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preminishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:04:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/02 01:41:50 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREMINISHELL_H
# define PREMINISHELL_H

#include "libft/libft.h"
#include "./pipex/prepipex.h"

# define __SKIP 2
# define __WHANG 0
# define __PRINT PRINT_ERROR
# define __PERROR PUT_ERROR
# define __EXIT_REACHED 7
# define __SUCCEED 9 //makes possible to know that the temporary file should not be deleted
# define __RADICAL "/tmp/ueyjq7ZbZhs26jd"
# define __FALLOC "failed allocation"
# define __SERROR "syntax error near unexpected token `newline'"

extern int	exitstatus;

typedef struct s_env
{
	char		*var;
	struct	s_env 	*next;
}			t_env;

typedef struct s_token
{
	char		*content;
	int		type;
	struct s_token *next;
}			t_token;

typedef	struct s_commands
{
	char	*main_command;
	char	**arguments;
	struct s_token		*tokens;
	struct s_commands	*next;
}			t_commands;

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
	char	*infile;
	char	*outfile;
	char	*limiter;
	char	*ftemp1;
	char	***lst;
	int		status;
	int		exit_code;
	int		p1[2];
	int		p2[2];
	int		jx;
	int		nb;
	int		infd;
	int		outfd;
	int		hdoc_fd;
	t_bool	flg_infile;
	t_bool	flg_outfile;
	t_bool	flg_heredoc;
	t_bool	flg_outappend;
	t_bool	flg_pipeline;
	t_ppex	*var;
}				t_vars;
#endif
