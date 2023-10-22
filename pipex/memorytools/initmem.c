/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initmem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:08:46 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/22 15:10:58 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_fdinit(t_ppex *var)
{
	var->pipe_outfd = -111;
	return (__TRUE);
}

t_bool	ft_init_p(t_ppex *var)
{
	int	i;

	i = 0;
	while (i < var->nbcmd)
	{
		var->p[i] = ft_calloc(2, sizeof(int));
		if (!var->p[i])
		{
			i--;
			while (i > -1)
			{
				free(var->p[i]);
				var->p[i] = NULL;
				i--;
			}
			free(var->p);
			var->p = NULL;
			return (__FALSE);
		}
		var->p[i][0] = -111;
		var->p[i][1] = -111;
		i++;
	}
	return (__TRUE);
}

t_bool	ft_inittab_int(t_ppex *var)
{
	int	i;

	i = 0;
	var->pid = ft_calloc(var->nbcmd, sizeof(int));
	if (!var->pid)
		return (__FALSE);
	while (i < var->nbcmd)
	{
		var->pid[i] = -111;
		i++;
	}
	var->p = ft_calloc(var->nbcmd, sizeof(int *));
	if (!var->p)
		return (free(var->pid), __FALSE);
	if (!ft_init_p(var))
		return (free(var->pid), __FALSE);
	return (__TRUE);
}

void	ft_set_nbcmd(t_ppex *var)
{
	t_commands	*iterator;

	iterator = var->commands;
	var->nbcmd = 0;
	while (iterator)
	{
		var->nbcmd++;
		iterator = iterator->next;
	}
}

t_ppex	*ft_init_tvars(t_commands *commands)
{
	t_ppex	*var;

	var = NULL;
	var = ft_calloc(1, sizeof(t_ppex));
	if (!var)
	{
		ft_leave(EXIT_FAILURE, \
		"in pipe part: ft_init_tvars(): ft_calloc() failed", __PRINT);
		exit(EXIT_FAILURE);
	}
	var->commands = commands;
	ft_set_nbcmd(var);
	if (!ft_fdinit(var))
		return (free(var), NULL);
	if (!ft_inittab_int(var))
		return (free(var), NULL);
	return (var);
}
