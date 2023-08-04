/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 10:27:13 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/04 10:36:44 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
