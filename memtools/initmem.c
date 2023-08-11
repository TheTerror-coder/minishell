/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initmem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:12 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/06 16:26:26 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_initfds(t_vars *v)
{
	v->p1[0] = -111;
	v->p1[1] = -111;
	v->p2[0] = -111;
	v->p2[1] = -111;
	v->infd = -111;
	v->outfd = -111;
	v->hdoc_fd = -111;
}

t_vars	*ft_initvars(void)
{
	t_vars	*v;

	v = ft_calloc(1, sizeof(t_vars));
	if (!v)
		return (NULL);
	ft_initfds(v);
	return (v);
}