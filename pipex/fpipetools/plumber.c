/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:03:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:02:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_plumber(t_vars *v)
{
	t_ppex	*var;
	int		fdbk;

	var = v->var;
	fdbk = __TRUE;
	free(var->pid);
	var->pid = NULL;
	if (!ft_close_tvars(v->var))
		ft_exitpipe(EXIT_FAILURE, v);
	fdbk = ft_setcmdpath(v);
	var->exit = EXIT_FAILURE;
	if (!fdbk || fdbk == __SKIP)
		ft_exitpipe(var->exit, v);
	execve(var->pathcmd, var->cmdlst[var->i], __environ);
	perror("execve");
	ft_exitpipe(EXIT_FAILURE, v);
	return (__FALSE);
}
