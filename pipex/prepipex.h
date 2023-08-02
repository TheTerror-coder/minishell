/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:00:47 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:00:54 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPIPEX_H
# define PREPIPEX_H

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

typedef struct s_ppex
{
	int		argc;
	char	**argv;
	char	***cmdlst;
	char	*pathcmd;
	char	**paths;
	char	*str;
	char	*set;
	int		status;
	int		i;
	int		d;
	int		jx;
	int		lcmd;
	int		infile_fd;
	int		outfile_fd;
	int		sp[2];
	int		**p;
	int		ff;
	int		*pid;
	int		exit;
}				t_ppex;

#endif
