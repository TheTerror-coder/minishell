/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:08:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/16 15:23:05 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_lnch_executable(t_vars *v)
{
	int	pid;

	if (ft_setcmdpath(v) != __TRUE)
		return (__FALSE);
	pid = -1;
	pid = fork();
	if (pid < 0)
		return (ft_goprompt("fork", __PERROR));
	if (!pid)
	{
		ft_freesecondaries(v);
		execve(v->cmdpath, v->argv, __environ);
		perror("execve");
		ft_exitprocss(v, __EXIT_REACHED);
	}
	waitpid(pid, &v->status, 0);
	if (WIFEXITED(v->status))
	{
		v->exit_code = WEXITSTATUS(v->status);
		if (v->exit_code != EXIT_SUCCESS && v->exit_code != __EXIT_REACHED)
			return (__FALSE);
	}
	return (__TRUE);
}
