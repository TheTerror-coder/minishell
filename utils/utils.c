/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:06 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/29 20:02:46 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_leave(t_vars *v, int code, char *msg, t_typ action)
{
	if (v)
		v->exitstatus = code;
	if (!msg)
		return (__FALSE);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (action == __PRINT)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	return (__FALSE);
}

t_bool	ft_ioset_op(t_vars *v, int *infd, int *outfd)
{
	if (*infd > -1)
	{
		if (close(STDIN_FILENO) == -1)
			return (ft_leave(v, EXIT_FAILURE, "close STDIN_FILENO", __PERROR));
		if (dup(*infd) == -1)
			return (ft_leave(v, EXIT_FAILURE, "dup infd", __PERROR));
		if (!ft_fclose(v, infd))
			return (ft_leave(v, v->exitstatus, "close infd", __PRINT));
	}
	if (*outfd > -1)
	{
		if (close(STDOUT_FILENO) == -1)
			return (ft_leave(v, EXIT_FAILURE, "close STDOUT_FILENO", __PERROR));
		if (dup(*outfd) == -1)
			return (ft_leave(v, EXIT_FAILURE, "dup outfd", __PERROR));
		if (!ft_fclose(v, outfd))
			return (ft_leave(v, v->exitstatus, "close outfd", __PRINT));
	}
	return (__TRUE);
}

t_bool	ft_fclose(t_vars *v, int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
			return (v->exitstatus = EXIT_FAILURE, __FALSE);
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
		ft_leave(v, EXIT_FAILURE, "ft_raz(): dup", __PERROR);
	ft_ioset_op(v, &in, &out);
	return (__TRUE);
}
