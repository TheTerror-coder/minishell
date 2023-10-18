/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initmem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:12 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/18 22:43:50 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_initfds(t_vars *v)
{
	v->p1[0] = -111;
	v->p1[1] = -111;
	v->p2[0] = -111;
	v->p2[1] = -111;
	v->infd = -111;
	v->outfd = -111;
	v->stdin = -111;
	v->stdout = -111;
	v->stdin = dup(STDIN_FILENO);
	v->stdout = dup(STDOUT_FILENO);
	if (v->stdout < 0 || v->stdin < 0)
		return (perror("dup"), __FALSE);
	v->hdoc_fd = -111;
	return (__TRUE);
}

t_vars	*ft_initvars(void)
{
	t_vars	*v;

	v = ft_calloc(1, sizeof(t_vars));
	if (!v)
		return (NULL);
	if (!ft_initfds(v))
		return (free(v), NULL);
	return (v);
}
