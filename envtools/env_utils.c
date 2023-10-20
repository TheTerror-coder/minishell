/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:27:13 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/20 07:18:27 by lmohin           ###   ########.fr       */
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

t_bool	free_tab(char **s, int size)
{
	while (size >= 0)
	{
		free(s[size]);
		size--;
	}
	free(s);
	return (__TRUE);
}

char	**env_list_to_tab(t_vars *v)
{
	char	**s;
	int	i;
	t_env	*cpy;

	i = 0;
	s = malloc(sizeof(char *) * (ft_envsize(v->my_env) + 1));
	if (!s)
		return (0);
	cpy = v->my_env;
	while (cpy)
	{
		s[i] = ft_strdup(cpy->var);
		if (!(s[i]))
		{
			free_tab(s, i);
			return (NULL);
		}
		i++;
		cpy = cpy->next;
	}
	s[i] = NULL;
	return (s);
}

char	*check_env_var_set(t_vars *v, char *var)
{
	t_env	*tmp;
	char	*sub_var;
	char	*var_equal;
	size_t	length_var;

	length_var = ft_strlen(var) + 1;
	var_equal = ft_strjoin(var, "=");
	if (!var_equal)
		return (NULL);
	tmp = v->my_env;
	if (!tmp)
	{
		free(var_equal);
		return (NULL);
	}
	while (tmp->next && ft_strncmp(tmp->var, var_equal, length_var))
		tmp = tmp->next;
	if (ft_strncmp(tmp->var, var_equal, length_var))
	{
		free(var_equal);
		return (NULL);
	}
	sub_var = \
		ft_substr(tmp->var, length_var, ft_strlen(tmp->var) - length_var + 1);
	if (!sub_var)
		return (NULL);
	free(var_equal);
	return (sub_var);
}

t_bool	ft_freeenv(t_vars *v)
{
	t_env *tmp;

	while ((v->my_env) != NULL)
	{
		tmp = (v->my_env)->next;
		free((v->my_env)->var);
		free(v->my_env);
		v->my_env = tmp;
	}
	return (__TRUE);
}
