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

void	ft_run_pipeline(t_vars *v, t_commands *commands)
{
	t_ppex	*var;

	var = NULL;
	var = ft_init_tvars(commands);
	v->var = var;
	if (!var)
		ft_exitpipe(EXIT_FAILURE, v);
	if (!ft_pipex(v))
		ft_exitpipe(exitstatus, v);
	ft_exitpipe(exitstatus, v);
}

t_bool	ft_pipex(t_vars *v)
{
	t_ppex	*var;
	int		fdbk;

	var = v->var;
	fdbk = __TRUE;
	var->iterator = var->commands;
	var->i = 0;
	while (var->i < var->nbcmd && var->iterator)
	{
		if (pipe(var->p[var->i]))
			return (ft_perror(EXIT_FAILURE, "pipe", __PERROR));
		var->skip_command_flg = __FALSE;
		fdbk = ft_ioset(v);
		if (!fdbk && !var->skip_command_flg)
			return (ft_perror(EXIT_FAILURE, NULL, __PRINT));
		if (!var->skip_command_flg)
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
		var->iterator = var->iterator->next;
	}
	return (__TRUE);
}
