/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 05:39:12 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/26 05:42:00 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_env(t_vars *v)
{
	t_env	*tmp;

	tmp = v->my_env;
	while (tmp->next != NULL)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
	if (tmp->var)
		printf("%s\n", tmp->var);
	return (0);
}
