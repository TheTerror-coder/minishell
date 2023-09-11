/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:43 by TheTerror         #+#    #+#             */
/*   Updated: 2023/09/11 06:48:58 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_lst(t_vars *v)
{
	int	i;

	i = 0;
	if (v->lst)
	{
		while (v->lst[i])
		{
			ft_free2str(&v->lst[i]);
			i++;
		}
		free(v->lst);
		v->lst = NULL;
	}
}

void	ft_freesecondaries(t_vars *v)
{
	ft_freestr(&v->line);
	ft_free2str(&v->paths);
	ft_freestr(&v->str);
	ft_freestr(&v->set);
	ft_freestr(&v->infile);
	ft_freestr(&v->outfile);
	ft_freestr(&v->limiter);
	ft_freestr(&v->ftemp1);
	ft_free_lst(v);
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

void	ft_exitprocss(t_vars *v, int status)
{
	if (!access(v->ftemp1, F_OK) && status != __SUCCEED)
		unlink(v->ftemp1);
	ft_closetvars(v);
	ft_freetvars(v);
	exit(status);
}
