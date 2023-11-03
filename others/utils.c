/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:06 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/02 20:00:11 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*dup_secured(t_vars *v, char *str)
{
	char	*dup;

	dup = ft_strdup(str);
	if (!dup)
		ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR);
	return (dup);
}

t_bool	ft_leave(t_vars *v, int code, char *msg, t_typ action)
{
	if (v)
	{
		v->exitstatus = code;
		v->flg_parsing_is_ok = __FALSE;
	}
	if (!msg)
		return (__FALSE);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (action == __PRINT)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	return (__FALSE);
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

t_bool	ft_pwait(t_vars *v, int pid, int option)
{
	int	ret;

	ret = waitpid(pid, &v->code, option);
	if (ret == -1)
		return (ft_leave(v, EXIT_FAILURE, "waitpid", __PERROR));
	if (ret == pid)
	{
		if (WIFEXITED(v->code))
			v->exitstatus = WEXITSTATUS(v->code);
	}
	if (v->exitstatus != 0)
		return (__FALSE);
	return (__TRUE);
}
