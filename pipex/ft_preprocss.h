/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preprocss.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:45:29 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:15:44 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PREPROCSS_H
# define FT_PREPROCSS_H

# include "include/libft/libft.h"

# define __AFAULT "arguments fault"
# define __MISSARG "missing arguments"
# define __MOREARG "too many arguments"
# define __PRINT PRINT_ERROR
# define __PERROR PUT_ERROR
# define __SKIP 2
# define __WHANG 0
# define __EXIT_NOCMD 7

# define __MXPATH 128
# define __LENBUF 5

typedef enum e_typ
{
	PRINT_ERROR = 666,
	PUT_ERROR = 777
}				t_typ;

typedef struct s_vars
{
	t_bool	heredoc_flg;
	t_bool	infile_flg;
	int		argc;
	char	**argv;
	char	*limiter;
	char	**awhich;
	char	***cmdlst;
	char	*cmdpath;
	char	**paths;
	int		status;
	int		i;
	int		lcmd;
	int		infile_fd;
	int		outfile_fd;
	int		sp[2];
	int		**p;
	int		ff;
	int		*pid;
	int		exit;
}				t_vars;

#endif
