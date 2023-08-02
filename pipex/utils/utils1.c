/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:19 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:02:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_perror(t_vars *v, int status, const char *msg, t_typ action)
{
	v->var->exit = status;
	if (!msg)
		return (__FALSE);
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
	while (i < v->var->lcmd)
	{
		if (v->var->pid[i] > 0)
		{
			fdbk = waitpid(v->var->pid[i], &v->var->status, __WHANG);
			if (fdbk == -1)
				return (ft_perror(v, EXIT_FAILURE, "waitpid", __PERROR));
			if (fdbk == v->var->pid[i])
			{
				if (WIFEXITED(v->var->status))
					v->var->exit = WEXITSTATUS(v->var->status);
				v->var->pid[i] = -111;
			}
		}
		i++;
	}
	return (__TRUE);
}

void	ft_exitpipe(int status, t_vars *v)
{
	if (v->var->pid)
		if (!ft_waitingroom(v))
			status = EXIT_FAILURE;
	status |= v->var->exit;
	ft_free_tvars(v->var);
	ft_exitprocss(v, status);
}
