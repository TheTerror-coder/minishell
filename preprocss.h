/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocss.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:04:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/26 04:38:27 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPROCSS_H
# define PREPROCSS_H

#include "libft/libft.h"

# define __SKIP 2
# define __WHANG 0
# define __PRINT PRINT_ERROR
# define __PERROR PUT_ERROR
# define __EXIT_REACHED 7

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
	int		status;
	int		exit_code;
	int		p1[2];
	int		p2[2];
	int		jx;
	int		infd;
	int		outfd;
	t_bool	flg_infile;
	t_bool	flg_outfile;
	t_bool	flg_heredoc;
	t_bool	flg_outappend;
}				t_vars;
#endif
