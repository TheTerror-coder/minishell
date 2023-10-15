/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:16:21 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/14 19:23:34 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_fwait(t_vars *v, int pid, int option)
{
	t_ppex	*var;
	int	ret;

	var = v->var;
	ret = waitpid(pid, &var->status, option);
	if (ret == -1)
		return (ft_perror(EXIT_FAILURE, "waitpid", __PERROR));
	if (ret == pid)
		if (WIFEXITED(var->status))
			exitstatus = WEXITSTATUS(var->status);
	return (__TRUE);
}
