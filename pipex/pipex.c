/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:43:39 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 16:39:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	ft_pipex(t_vars *v);

t_bool	ft_pipeline(t_vars *v, int nbcmd, char ***cmdlst)
{
	t_ppex	*var;

	var = NULL;
	var = ft_init_tvars(nbcmd, cmdlst);
	v->var = var;
	if (!var)
		ft_exitpipe(EXIT_FAILURE, v);
	if (!ft_checkargs(v))
		ft_exitpipe(var->exit, v);
// ft_set_cmdlist(v);
// ft_putendl_fd("eheheeheh", 2);

	if (!ft_pipex(v))
		ft_exitpipe(exitstatus, v);
	ft_exitpipe(exitstatus, v);
	return (__TRUE);
}

t_bool	ft_pipex(t_vars *v)
{
	t_ppex	*var;
	int		fdbk;

	var = v->var;
	fdbk = __TRUE;
	while (var->i < var->nbcmd)
	{
		if (pipe(var->p[var->i]))
			return (ft_perror(EXIT_FAILURE, "pipe", __PERROR));
		fdbk = ft_ioset(v);
		if (!fdbk)
			return (ft_perror(EXIT_FAILURE, NULL, __PRINT));
		if (fdbk != __SKIP)
		{
			var->pid[var->i] = fork();
			if (var->pid[var->i] == -1)
				return (ft_perror(EXIT_FAILURE, "fork", __PERROR));
			if (!var->pid[var->i])
				ft_plumber(v);
		}
		if (!ft_pcloser(v))
			return (ft_perror(EXIT_FAILURE, NULL, __PRINT));
		var->i++;
	}
	return (__TRUE);
}
