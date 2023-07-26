/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 04:55:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/26 10:15:24 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	get_var_name(char **var, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	*var = ft_substr(str, 0, i + 1);
	if (!(*var))
		return (__FALSE);
	return (__TRUE);
}

t_bool	find_var(t_vars *v, char *var, char *str)
{
	t_env *tmp;

	tmp = v->my_env;
	while (tmp->next && strncmp(tmp->var, var, ft_strlen(var)))
		tmp = tmp->next;
	if (strncmp(tmp->var, var, ft_strlen(var)))
		return (__FALSE);
	free(tmp->var);
	tmp->var = str;
	return (__TRUE);
}	
t_bool	ft_export(t_vars *v, char *str)
{
	char	*var;

	get_var_name(&var, str);
	if (!find_var(v, var, str) && strchr(str, '='))
		add_env_var(v, str);	
	return (0);
}
