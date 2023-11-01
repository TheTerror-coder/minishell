/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:19 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/01 13:10:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_perror(t_vars *v, int code, const char *msg, t_typ action)
{
	if (v)
		v->exitstatus = code;
	if (!msg)
		return (__FALSE);
	ft_putendl_fd("minishell: ", STDERR_FILENO);
	if (action == __PERROR)
		perror(msg);
	else
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
	return (__FALSE);
}

t_bool	ft_waitingroom(t_vars *v)
{
	int	i;
	int	fdbk;

	i = 0;
	fdbk = 0;
	while (i < v->var->nbcmd)
	{
		if (v->var->pid[i] > 0)
		{
			fdbk = waitpid(v->var->pid[i], &v->var->code, __WHANG);
			if (fdbk == -1)
				return (ft_perror(v, EXIT_FAILURE, "waitpid", __PERROR));
			if (fdbk == v->var->pid[i])
			{
				if (WIFEXITED(v->var->code))
					v->exitstatus = WEXITSTATUS(v->var->code);
				v->var->pid[i] = -111;
			}
		}
		i++;
	}
	return (__TRUE);
}

t_bool	ft_fwait(t_vars *v, int pid, int option)
{
	t_ppex	*var;
	int		ret;

	var = v->var;
	ret = waitpid(pid, &var->code, option);
	if (ret == -1)
		return (ft_perror(v, EXIT_FAILURE, "waitpid", __PERROR));
	if (ret == pid)
	{
		if (WIFEXITED(var->code))
			v->exitstatus = WEXITSTATUS(var->code);
	}
	return (__TRUE);
}
