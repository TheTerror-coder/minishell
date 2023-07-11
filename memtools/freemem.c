/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:43 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/11 19:51:53 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_freetvars(t_vars *v)
{
	if (v->line)
		free(v->line);
	if (v->argv)
		ft_freesplit(v->argv);
	if (v->paths)
		ft_freesplit(v->paths);
	if (v->cmdpath)
		free(v->cmdpath);
	free(v);
	v = NULL;
}

void	ft_exitprocss(t_vars *v, int status)
{
	ft_freetvars(v);
	exit(status);
}