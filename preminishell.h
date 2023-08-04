/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preminishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:04:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/28 14:51:23 by TheTerror        ###   ########lyon.fr   */
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

typedef struct s_env
{
	char		*var;
	struct	s_env 	*next;
}			t_env;

typedef struct s_vars
{
	t_env	*my_env;
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
	t_bool	flg_infile;
	t_bool	flg_outfile;
	t_bool	flg_heredoc;
	t_bool	flg_outappend;
	t_bool	flg_pipeline;
	t_ppex	*var;
}				t_vars;
#endif
