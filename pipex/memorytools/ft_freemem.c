/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:06:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 12:51:33 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memtools.h"

void	ft_free_cmdlst(t_vars *var)
{
	int	i;

	i = 0;
	if (var->cmdlst)
	{
		while (i < var->lcmd)
		{
			if (var->cmdlst[i])
				ft_freesplit(var->cmdlst[i]);
			var->cmdlst[i] = NULL;
			i++;
		}
		free(var->cmdlst);
		var->cmdlst = NULL;
	}
}

void	ft_free_p(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->lcmd)
	{
		free(var->p[i]);
		var->p[i] = NULL;
		i++;
	}
	free(var->p);
	var->p = NULL;
}

void	ft_free_tvars(t_vars *var)
{
	ft_close_tvars(var);
	if (var->limiter)
		free(var->limiter);
	if (var->awhich)
		ft_freesplit(var->awhich);
	if (var->cmdlst)
		ft_free_cmdlst(var);
	if (var->cmdpath)
		free(var->cmdpath);
	if (var->paths)
		ft_freesplit(var->paths);
	if (var->p)
		ft_free_p(var);
	if (var->pid)
		free(var->pid);
	free(var);
	var = NULL;
}
