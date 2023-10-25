/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:06:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/25 18:20:48 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_exitpipe(t_vars *v)
{
	if (v->var->pid)
		ft_waitingroom(v);
	ft_free_tvars(v->var);
	v->var = NULL;
	ft_exitbackprocss(v, exitstatus);
}

void	ft_free_p(t_ppex *var)
{
	int	i;

	i = 0;
	while (i < var->nbcmd)
	{
		free(var->p[i]);
		var->p[i] = NULL;
		i++;
	}
	free(var->p);
	var->p = NULL;
}

void	ft_free_tvars(t_ppex *var)
{
	ft_close_tvars(var);
	ft_freestr(&var->pathcmd);
	ft_free2str(&var->paths);
	if (var->p)
		ft_free_p(var);
	if (var->pid)
		free(var->pid);
	var->pid = NULL;
	free(var);
	var = NULL;
}
