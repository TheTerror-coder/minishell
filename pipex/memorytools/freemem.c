/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:06:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/14 19:24:58 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

// void	ft_free_cmdlst(t_ppex *var)
// {
// 	int	i;

// 	i = 0;
// 	if (var->cmdlst)
// 	{
// 		while (i < var->nbcmd)
// 		{
// 			ft_free2str(&var->cmdlst[i]);
// 			i++;
// 		}
// 		free(var->cmdlst);
// 		var->cmdlst = NULL;
// 	}
// }

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
	// if (var->cmdlst)
	// 	ft_free_cmdlst(var);
	ft_freestr(&var->pathcmd);
	ft_free2str(&var->paths);
	ft_freestr(&var->str);
	ft_freestr(&var->set);
	if (var->p)
		ft_free_p(var);
	if (var->pid)
		free(var->pid);
	var->p = NULL;
	var->pid = NULL;
	free(var);
	var = NULL;
}
