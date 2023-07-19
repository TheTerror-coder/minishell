/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:19 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/07 15:13:38 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

t_bool	ft_checkinfile(t_vars *var)
{
	if (!var->heredoc_flg)
		if (access(var->argv[1], R_OK) < 0)
			return (ft_perror(var, EXIT_SUCCESS, var->argv[1], __PERROR));
	return (__TRUE);
}

t_bool	ft_perror(t_vars *var, int status, const char *msg, t_typ action)
{
	var->exit = status;
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

t_bool	ft_waitingroom(t_vars *var)
{
	int	i;
	int	fdbk;

	i = 0;
	fdbk = 0;
	while (i < var->lcmd)
	{
		if (var->pid[i] > 0)
		{
			fdbk = waitpid(var->pid[i], &var->status, __WHANG);
			if (fdbk == -1)
				return (ft_perror(var, EXIT_FAILURE, "waitpid", __PERROR));
			if (fdbk == var->pid[i])
			{
				if (WIFEXITED(var->status))
					var->exit = WEXITSTATUS(var->status);
				var->pid[i] = -111;
			}
		}
		i++;
	}
	return (__TRUE);
}

void	ft_exitprocss(int status, t_vars *var)
{
	if (var->pid)
		if (!ft_waitingroom(var))
			status = EXIT_FAILURE;
	status |= var->exit;
	ft_free_tvars(var);
	exit(status);
}
