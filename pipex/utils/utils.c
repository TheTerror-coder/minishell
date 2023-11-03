/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:19 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/03 14:40:06 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_set_exitstatus(t_vars *v, t_bool *flg_signal);

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
	int		i;
	int		fdbk;
	t_bool	flg_signal;

	i = 0;
	fdbk = 0;
	flg_signal = 0;
	while (i < v->var->nbcmd)
	{
		if (v->var->pid[i] > 0)
		{
			fdbk = waitpid(v->var->pid[i], &v->var->code, __WHANG);
			if (fdbk == -1)
				return (ft_perror(v, EXIT_FAILURE, "waitpid", __PERROR));
			if (fdbk == v->var->pid[i])
			{
				ft_set_exitstatus(v, &flg_signal);
				v->var->pid[i] = -111;
			}
		}
		i++;
	}
	if (flg_signal == 130)
		ft_putstr_fd("\n", 1);
	return (__TRUE);
}

void	ft_set_exitstatus(t_vars *v, t_bool *flg_signal)
{
	if (WIFEXITED(v->var->code))
		v->exitstatus = WEXITSTATUS(v->var->code);
	if (WIFSIGNALED(v->var->code))
	{
		v->exitstatus = 128 + WTERMSIG(v->var->code);
		*flg_signal = 128 + WTERMSIG(v->var->code);
	}
}
