/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:43 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/21 20:23:08 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_freesecondaries(t_vars *v)
{
	if (v->line)
		free(v->line);
	v->line = NULL;
	if (v->paths)
		ft_freesplit(v->paths);
	v->paths = NULL;
	if (v->str)
		free(v->str);
	v->str = NULL;
	if (v->set)
		free(v->set);
	v->set = NULL;
	if (v->infile)
		free(v->infile);
	v->infile = NULL;
	if (v->outfile)
		free(v->outfile);
	v->outfile = NULL;
	if (v->limiter)
		free(v->limiter);
	v->limiter = NULL;
}

void	ft_freetvars(t_vars *v)
{
	ft_freesecondaries(v);
	if (v->argv)
		ft_freesplit(v->argv);
	v->argv = NULL;
	if (v->cmdpath)
		free(v->cmdpath);
	v->cmdpath = NULL;
	free(v);
	v = NULL;
}

void	ft_exitprocss(t_vars *v, int status)
{
	ft_freetvars(v);
	exit(status);
}