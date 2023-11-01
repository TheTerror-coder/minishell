/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freemem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:43 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/01 13:14:23 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freesecondaries(t_vars *v)
{
	ft_freestr(&v->pwd);
	ft_freestr(&v->line);
	ft_free2str(&v->paths);
	ft_freestr(&v->str);
	ft_freestr(&v->limiter);
	ft_freestr(&v->ftemp1);
}

void	ft_freetvars(t_vars *v)
{
	ft_freesecondaries(v);
	ft_freestr(&v->cmdpath);
	free_env(v);
	ft_freecommands(v);
	free(v->var);
	free(v);
	v = NULL;
}

t_bool	ft_closetvars(t_vars *v)
{
	int	fdbk;

	fdbk = __TRUE;
	fdbk = fdbk && ft_fclose(v, &v->p1[0]);
	fdbk = fdbk && ft_fclose(v, &v->p1[1]);
	fdbk = fdbk && ft_fclose(v, &v->p2[0]);
	fdbk = fdbk && ft_fclose(v, &v->p2[1]);
	fdbk = fdbk && ft_fclose(v, &v->infd);
	fdbk = fdbk && ft_fclose(v, &v->outfd);
	fdbk = fdbk && ft_fclose(v, &v->hdoc_fd);
	if (!fdbk)
		v->exitstatus = EXIT_FAILURE;
	return (fdbk);
}

t_bool	free_env(t_vars *v)
{
	ft_clear_created_tempfiles(v);
	ft_closetvars(v);
	ft_fclose(v, &v->stdin);
	ft_fclose(v, &v->stdout);
	ft_freetvars(v);
	exit(code);
}

void	ft_exitbackprocss(t_vars *v, int code)
{
	ft_closetvars(v);
	ft_fclose(v, &v->stdin);
	ft_fclose(v, &v->stdout);
	ft_freetvars(v);
	close(0);
	close(1);
	exit(code);
}
