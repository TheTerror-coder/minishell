/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iosetter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:13:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/06/02 18:17:51 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipetools.h"

t_bool	ft_io_firstcmnd(t_vars *var);
t_bool	ft_io_lastcmnd(t_vars *var);
t_bool	ft_ioset_op(t_vars *var, int *infd, int *outfd);

t_bool	ft_ioset(t_vars *var)
{
	if (var->i == 0)
	{
		if (!ft_io_firstcmnd(var))
			return (__FALSE);
	}
	else if (var->i < (var->lcmd - 1))
	{
		if (!ft_ioset_op(var, &var->ff, &var->p[var->i][1]))
			return (__FALSE);
	}
	else
	{
		if (!ft_io_lastcmnd(var))
			return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_io_firstcmnd(t_vars *var)
{
	if (var->heredoc_flg)
		return (__TRUE);
	var->infile_fd = open(var->argv[1], O_RDONLY);
	if (var->infile_fd == -1)
		return (ft_perror(var, EXIT_FAILURE, "open", __PERROR));
	if (!ft_ioset_op(var, &var->infile_fd, &var->p[0][1]))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_io_lastcmnd(t_vars *var)
{
	if (var->heredoc_flg)
		var->outfile_fd = open(var->argv[var->argc - 1], \
					O_CREAT | O_WRONLY | O_APPEND, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	else
		var->outfile_fd = open(var->argv[var->argc - 1], \
					O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (var->outfile_fd == -1)
		return (ft_perror(var, EXIT_FAILURE, var->argv[var->argc - 1], \
							__PERROR));
	if (!ft_ioset_op(var, &var->ff, &var->outfile_fd))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_ioset_op(t_vars *var, int *infd, int *outfd)
{
	if (*infd > -1)
	{
		if (close(STDIN_FILENO) == -1)
			return (ft_perror(var, EXIT_FAILURE, "close STDIN_FILENO", \
								__PERROR));
		if (dup(*infd) == -1)
			return (ft_perror(var, EXIT_FAILURE, "dup infd", __PERROR));
		if (!ft_fclose(infd))
			return (ft_perror(var, EXIT_FAILURE, "close infd", __PRINT));
	}
	if (*outfd > -1)
	{
		if (close(STDOUT_FILENO) == -1)
			return (ft_perror(var, EXIT_FAILURE, "close STDOUT_FILENO", \
								__PERROR));
		if (dup(*outfd) == -1)
			return (ft_perror(var, EXIT_FAILURE, "dup outfd", __PERROR));
		if (!ft_fclose(outfd))
			return (ft_perror(var, EXIT_FAILURE, "close outfd", __PRINT));
	}
	return (__TRUE);
}
