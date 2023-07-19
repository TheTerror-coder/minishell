/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:43:39 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 17:23:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

t_bool	ft_pipex(t_vars *var);

int	main(int argc, char *argv[])
{
	t_vars	*var;

	var = NULL;
	var = ft_init_tvars(argc, argv);
	if (!var)
		ft_exitprocss(EXIT_FAILURE, var);
	if (!ft_checkargs(var))
		ft_exitprocss(var->exit, var);
	if (!ft_set_cmdlist(var))
		ft_exitprocss(EXIT_FAILURE, var);
	if (!ft_setpath(var))
		ft_exitprocss(EXIT_FAILURE, var);
	if (!ft_pipex(var))
		ft_exitprocss(var->exit, var);
	ft_exitprocss(var->exit, var);
	return (EXIT_SUCCESS);
}

t_bool	ft_pipex(t_vars *var)
{
	if (!ft_checkinfile(var))
		var->infile_flg = __FALSE;
	while (var->i < var->lcmd)
	{
		if (pipe(var->p[var->i]))
			return (ft_perror(var, EXIT_FAILURE, "pipe", __PERROR));
		if (var->infile_flg)
		{
			if (!ft_ioset(var))
				return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
			var->pid[var->i] = fork();
			if (var->pid[var->i] == -1)
				return (ft_perror(var, EXIT_FAILURE, "fork", __PERROR));
			if (!var->pid[var->i])
				ft_plumber(var);
		}
		if (!ft_pcloser(var))
			return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
		var->i++;
		var->infile_flg = __TRUE;
	}
	return (__TRUE);
}
