/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:26:44 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/28 06:17:15 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_envsize(t_env *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

t_bool	free_tab(char **s, int	size)
{
	while (size >= 0)
	{
		free(s[size]);
		size--;
	}
	free(s);
	return (0);
}

char	**env_list_to_tab(t_vars *v)
{
	char	**s;
	int	i;
	t_env	*cpy;

	i = 0;
	s = malloc(sizeof(char *) *  (ft_envsize(v->my_env) + 1));
	if (!s)
		return (0);
	cpy = v->my_env;
	while (cpy)
	{
		s[i] = ft_strdup(cpy->var);
		if (!(s[i]))
		{
			free_tab(s, i);
			return (0);
		}
		i++;
		cpy = cpy->next;
	}
	s[i] = NULL;
	return (s);
}

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
