/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:12:23 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/31 19:59:21 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if (WIFSIGNALED(v->code))
		{
			ft_putnbr_fd(WTERMSIG(v->code), 2);
			v->exitstatus = 128 + WTERMSIG(v->code);
			return (__FALSE);
		}
	}
	return (__TRUE);
}
