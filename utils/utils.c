/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:06 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/22 13:40:35 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_leave(int status, char *msg, t_typ action)
{
	exitstatus = status;
	if (!msg)
		return (__FALSE);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (action == __PRINT)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	return (__FALSE);
}

t_bool	ft_ioset_op(int *infd, int *outfd)
{
	if (*infd > -1)
	{
		if (close(STDIN_FILENO) == -1)
			return (ft_leave(EXIT_FAILURE, "close STDIN_FILENO", __PERROR));
		if (dup(*infd) == -1)
			return (ft_leave(EXIT_FAILURE, "dup infd", __PERROR));
		if (!ft_fclose(infd))
			return (ft_leave(exitstatus, "close infd", __PRINT));
	}
	if (*outfd > -1)
	{
		if (close(STDOUT_FILENO) == -1)
			return (ft_leave(EXIT_FAILURE, "close STDOUT_FILENO", __PERROR));
		if (dup(*outfd) == -1)
			return (ft_leave(EXIT_FAILURE, "dup outfd", __PERROR));
		if (!ft_fclose(outfd))
			return (ft_leave(exitstatus, "close outfd", __PRINT));
	}
	return (__TRUE);
}

t_bool	ft_fclose(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
			return (exitstatus = EXIT_FAILURE, __FALSE);
		*fd = -111;
	}
	return (__TRUE);
}

t_bool	ft_raz(t_vars *v)
{
	int	in;
	int	out;

	in = __CLOSED_FD;
	out = __CLOSED_FD;
	v->flg_exit_main_procss = __FALSE;
	in = dup(v->stdin);
	out = dup(v->stdout);
	if (out < 0 || in < 0)
		ft_leave(EXIT_FAILURE, "ft_raz(): dup", __PERROR);
	ft_ioset_op(&in, &out);
	return (__TRUE);
}
