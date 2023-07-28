/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:43 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/26 14:53:10 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_freesecondaries(t_vars *v)
{
	ft_freestr(&v->line);
	if (v->paths)
		ft_free2str(&v->paths);
	v->paths = NULL;
	ft_freestr(&v->str);
	ft_freestr(&v->set);
	ft_freestr(&v->infile);
	ft_freestr(&v->outfile);
	ft_freestr(&v->limiter);
	ft_freestr(&v->ftemp1);
}

void	ft_freetvars(t_vars *v)
{
	ft_freesecondaries(v);
	if (v->argv)
		ft_free2str(&v->argv);
	v->argv = NULL;
	if (v->cmdpath)
		free(v->cmdpath);
	v->cmdpath = NULL;
	free(v);
	v = NULL;
}

void	ft_closetvars(t_vars *v)
{
	ft_fclose(&v->p1[0]);
	ft_fclose(&v->p1[1]);
	ft_fclose(&v->p2[0]);
	ft_fclose(&v->p2[1]);
	ft_fclose(&v->infd);
	ft_fclose(&v->outfd);
}

void	ft_exitprocss(t_vars *v, int status)
{
	if (!access(v->ftemp1, F_OK) && status != __SUCCEED)
		unlink(v->ftemp1);
	ft_closetvars(v);
	ft_freetvars(v);
	exit(status);
}