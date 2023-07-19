/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plumber.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:03:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 17:25:08 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipetools.h"

t_bool	ft_plumber(t_vars *var)
{
	int	fdbk;

	fdbk = __TRUE;
	free(var->pid);
	var->pid = NULL;
	if (var->i == 0 && var->heredoc_flg)
		if (!ft_heredoc(var))
			ft_exitprocss(EXIT_FAILURE, var);
	if (!ft_close_tvars(var))
		ft_exitprocss(EXIT_FAILURE, var);
	fdbk = ft_setcmdpath(var);
	var->exit = EXIT_FAILURE;
	if (!fdbk || fdbk == __SKIP)
		ft_exitprocss(var->exit, var);
	execve(var->cmdpath, var->cmdlst[var->i], __environ);
	perror("execve");
	ft_exitprocss(EXIT_FAILURE, var);
	return (__FALSE);
}
