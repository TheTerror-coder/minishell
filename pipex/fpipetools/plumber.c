/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:03:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/14 19:23:54 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_plumber(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	free(var->pid);
	var->pid = NULL;
	if (!ft_close_tvars(v->var))
		ft_exitpipe(EXIT_FAILURE, v);
	ft_freestr(&var->pathcmd);
	var->pathcmd = ft_set_cmdpath(v, var->iterator->arguments);
// ft_putendl_fd(var->pathcmd, 2);
	if (!var->pathcmd)
		ft_exitpipe(EXIT_FAILURE, v);
	execve(var->pathcmd, var->iterator->arguments, __environ);
	perror("plumber execve");
	ft_exitpipe(EXIT_FAILURE, v);
	return (__FALSE);
}
