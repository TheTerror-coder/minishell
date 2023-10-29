/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:27:13 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/29 21:24:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_envsize(t_env *lst)
{
	size_t	i;

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

char	**env_list_to_tab(t_vars *v)
{
	char	**tab;
	size_t	i;
	t_env	*env_cpy;

	i = 0;
	tab = malloc(sizeof(char *) * (ft_envsize(v->my_env) + 1));
	if (!tab)
		return (ft_leave(v, EXIT_FAILURE, "malloc", __PERROR), NULL);
	env_cpy = v->my_env;
	while (env_cpy)
	{
		tab[i] = ft_strdup(env_cpy->var);
		if (!(tab[i]))
		{
			ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR);
			return (ft_free2str(&tab), NULL);
		}
		i++;
		env_cpy = env_cpy->next;
	}
	tab[i] = NULL;
	return (tab);
}

t_bool	check_env_var_set(t_env *my_env, char *var)
{
	size_t	len;

	len = ft_strlen(var);
	while (my_env->next && (ft_strncmp(my_env->var, var, len) \
		|| (my_env->var)[len] != '='))
	{
		my_env = my_env->next;
	}
	if (ft_strncmp(my_env->var, var, len) || (my_env->var)[len] != '=')
		return (__FALSE);
	if ((my_env->var)[len + 1] == '\0')
		return (__FALSE);
	return (__TRUE);
}

char	*get_env_var_content(t_vars *v, t_env *my_env, char *var)
{
	char	*content;
	size_t	len;

	len = ft_strlen(var);
	while (my_env->next && (ft_strncmp(my_env->var, var, len) \
		|| (my_env->var)[len] != '='))
	{
		my_env = my_env->next;
	}
	content = ft_substr(my_env->var, len + 1, ft_strlen(my_env->var) - len);
	if (!content)
		return (ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR), NULL);
	return (content);
}

t_bool	free_env(t_vars *v)
{
	t_env	*tmp;

	while ((v->my_env) != NULL)
	{
		tmp = (v->my_env)->next;
		free((v->my_env)->var);
		free(v->my_env);
		v->my_env = tmp;
	}
	return (__TRUE);
}
