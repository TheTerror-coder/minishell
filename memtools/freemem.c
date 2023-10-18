/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:43 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/18 22:38:26 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freesecondaries(t_vars *v)
{
	ft_freestr(&v->line);
	ft_free2str(&v->paths);
	ft_freestr(&v->str);
	ft_freestr(&v->set);
	ft_freestr(&v->limiter);
	ft_freestr(&v->ftemp1);
}

void	ft_freetvars(t_vars *v)
{
	ft_freesecondaries(v);
	ft_free2str(&v->argv);
	ft_freestr(&v->cmdpath);
	ft_freeenv(v);
	ft_freecommands(v);
	if (v->var)
		free(v->var);
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

	ft_fclose(&v->hdoc_fd);
}

void	ft_exitmainprocss(t_vars *v, int status)
{
	ft_clear_created_tempfiles(v);
	ft_closetvars(v);
	ft_fclose(&v->stdin);
	ft_fclose(&v->stdout);
	ft_freetvars(v);
	exit(status);
}

void	ft_exitbackprocss(t_vars *v, int status)
{
	ft_closetvars(v);
	ft_freetvars(v);
	exit(status);
}
