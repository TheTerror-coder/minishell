/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 05:39:12 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/06 04:47:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_env(t_vars *v)
{
	t_env	*tmp;

	if ((v->argv)[1])
	{
		ft_putstr_fd("minishell: ft_env: not handling parameters", 1);
		return (__FALSE);
	}
	tmp = v->my_env;
	while (tmp->next != NULL)
	{
		ft_putstr_fd(tmp->var, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	if (tmp->var)
	{
		ft_putstr_fd(tmp->var, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	return (__TRUE);
}
