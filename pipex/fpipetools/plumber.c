/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:03:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/18 16:02:58 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_plumber(t_vars *v)
{
	int		fdbk;
	t_ppex	*var;

	fdbk = __TRUE;
	var = v->var;
	free(var->pid);
	var->pid = NULL;
	if (!ft_close_tvars(v->var))
		ft_exitpipe(EXIT_FAILURE, v);
	fdbk = ft_run_builtin(v, var->iterator);
	if (fdbk == __TRUE)
		ft_exitpipe(EXIT_SUCCESS, v);
	if (fdbk == __FALSE)
		ft_exitpipe(EXIT_FAILURE, v);
	ft_freestr(&var->pathcmd);
	var->pathcmd = ft_set_cmdpath(v, var->iterator->main_command);
	if (!var->pathcmd)
		ft_exitpipe(EXIT_FAILURE, v);
	execve(var->pathcmd, var->iterator->arguments, v->envp);
	perror("plumber execve");
	ft_exitpipe(EXIT_FAILURE, v);
	return (__FALSE);
}
