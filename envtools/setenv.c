/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:26:44 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/26 04:54:50 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	add_env_var(t_vars *v, char *var)
{
	t_env	*tmp;
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->next = NULL;
	tmp = v->my_env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->var = ft_strdup(var);
	tmp->next = new;
	return (0);
}

t_bool	ft_setenv(t_vars *v)
{
	t_env		*dup_env;
	int		i;

	dup_env = malloc(sizeof(t_env));
	dup_env->next = NULL;
	dup_env->var = (v->envp)[0];
	v->my_env = dup_env;
	i = 1;
	while ((v->envp)[i])
	{
		add_env_var(v, (v->envp)[i]);
		i++;
	}
	return (0);
}
