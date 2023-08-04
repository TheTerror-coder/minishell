/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iosetter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:13:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/03 21:04:19 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_io_firstcmnd(t_vars *v);
t_bool	ft_io_lastcmnd(t_vars *v);
t_bool	ft_op_ioset(t_vars *v, int *infd, int *outfd);

t_bool	ft_ioset(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (var->i == 0)
	{
		if (!ft_io_firstcmnd(v))
			return (__FALSE);
	}
	else if (var->i < (var->nbcmd - 1))
	{
		if (!ft_op_ioset(v, &var->ff, &var->p[var->i][1]))
			return (__FALSE);
	}
	else
	{
		if (!ft_io_lastcmnd(v))
			return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_io_firstcmnd(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (var->infile_fd < 0)
		return (ft_perror(v, EXIT_FAILURE, "infile_fd error", __PRINT));
	if (!ft_op_ioset(v, &var->infile_fd, &var->p[0][1]))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_io_lastcmnd(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
// ft_putendl_fd("hehhhe", 2);
// ft_putendl_fd(var->cmdlst[var->i][0], 2);
	if (var->outfile_fd < 0)
		return (ft_perror(v, EXIT_FAILURE, "outfile_fd error", __PERROR));
	if (!ft_op_ioset(v, &var->ff, &var->outfile_fd))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_op_ioset(t_vars *v, int *infd, int *outfd)
{
	if (*infd > -1)
	{
		if (close(STDIN_FILENO) == -1)
			return (ft_perror(v, EXIT_FAILURE, "close STDIN_FILENO", \
								__PERROR));
		if (dup(*infd) == -1)
			return (ft_perror(v, EXIT_FAILURE, "dup infd", __PERROR));
		if (!ft_fclose0(infd))
			return (ft_perror(v, EXIT_FAILURE, "close infd", __PRINT));
	}
	if (*outfd > -1)
	{
		if (close(STDOUT_FILENO) == -1)
			return (ft_perror(v, EXIT_FAILURE, "close STDOUT_FILENO", \
								__PERROR));
		if (dup(*outfd) == -1)
			return (ft_perror(v, EXIT_FAILURE, "dup outfd", __PERROR));
		if (!ft_fclose0(outfd))
			return (ft_perror(v, EXIT_FAILURE, "close outfd", __PRINT));
	}
	return (__TRUE);
}
