/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:26:44 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/29 02:22:16 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	add_env_var(t_vars *v, char *var)
{
	t_env	*tmp;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (__FALSE);
	new->next = NULL;
	tmp = v->my_env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	new->var = ft_strdup(var);
	if (!(new->var))
	{
		free(new);
		return (__FALSE);
	}
	tmp->next = new;
	return (__TRUE);
}

t_bool	ft_setenv(t_vars *v, char **envp)
{
	t_env		*dup_env;
	int		i;

	dup_env = malloc(sizeof(t_env));
	if (!dup_env)
		return (__FALSE);
	dup_env->next = NULL;
	if (!(envp[0]))
	{
		dup_env->var = ft_strdup("SHLVL=1");
		v->my_env = dup_env;
		return (__TRUE);
	}
	dup_env->var = ft_strdup(envp[0]);
	if (!(dup_env->var))
	{
		free(dup_env);
		return (__FALSE);
	}
	v->my_env = dup_env;
	i = 1;
	while (envp[i])
	{
		if (!add_env_var(v, envp[i]))
			return (__FALSE);
		i++;
	}
	return (__TRUE);
}
