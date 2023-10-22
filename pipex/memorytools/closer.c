/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:49:42 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/22 15:44:06 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_close_tvars(t_ppex *var)
{
	int		i;
	t_bool	fdbk;

	i = 0;
	fdbk = __TRUE;
	if (var->p)
	{
		while (i < var->nbcmd)
		{
			fdbk = ft_fclose(&var->p[i][0]) & fdbk;
			fdbk = ft_fclose(&var->p[i][1]) & fdbk;
			i++;
		}
	}
	fdbk = ft_fclose(&var->pipe_outfd) & fdbk;
	return (fdbk);
}

t_bool	ft_pcloser(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (!ft_fclose(&var->pipe_outfd))
		return (ft_perror(EXIT_FAILURE, NULL, __PRINT));
	var->pipe_outfd = dup(var->p[var->i][0]);
	if (!ft_fclose(&var->p[var->i][0]))
		return (ft_perror(EXIT_FAILURE, NULL, __PRINT));
	if (!ft_fclose(&var->p[var->i][1]))
		return (ft_perror(EXIT_FAILURE, NULL, __PRINT));
	if (var->pipe_outfd < 0)
		return (ft_perror(EXIT_FAILURE, "dup", __PERROR));
	return (__TRUE);
}
