/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 04:55:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/15 08:34:04 by lmohin           ###   ########.fr       */
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
	t_env	*tmp;

	tmp = v->my_env;
	while (tmp->next && strncmp(tmp->var, var, ft_strlen(var)))
		tmp = tmp->next;
	if (strncmp(tmp->var, var, ft_strlen(var)))
		return (__FALSE);
	free(tmp->var);
	tmp->var = ft_strdup(str);
	return (__TRUE);
}

char	*adding_quotes(char *s)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * ft_strlen(s) + 3);
	if (!ret)
		return (0);
	i = 0;
	while (s[i] != '=' && s[i])
	{
		ret[i] = s[i];
		i++;
	}
	if (s[i] == '\0')
	{
		ret[i] = '\0';
		return (ret);
	}
	ret[i++] = '=';
	ret[i] = '"';
	while (s[i])
	{
		ret[i + 1] = s[i];
		i++;
	}
	ret[i + 1] = '"';
	ret[i + 2] = '\0';
	return (ret);
}

t_bool	print_export(t_vars *v)
{
	char	**s;
	char	*tmp;
	int		i;

	i = 0;
	s = env_list_to_tab(v);
	while (s[i] != NULL)
	{
		i++;
		if (s[i] != NULL && strncmp(s[i], s[i - 1], ft_strlen(s[i])) < 0)
		{
			tmp = s[i];
			s[i] = s[i - 1];
			s[i - 1] = tmp;
			i = 0;
		}
	}
	i = 0;
	while (s[i])
	{
		tmp = adding_quotes(s[i]);
		if (!tmp)
			return (1);
		printf("declare -x %s\n", adding_quotes(s[i++]));
		free(tmp);
	}
	return (0);
}

t_bool	export_one_arg(t_vars *v, char *str)
{
	char	*var;

	get_var_name(&var, str);
	if (!find_var(v, var, str))
		add_env_var(v, str);
	return (0);
}

t_bool	ft_export(t_vars *v, char **arguments)
{
	int	index;

	if (!arguments[1])
	{
		print_export(v);
		return (0);
	}
	else
	{
		index = 1;
		while (arguments[index])
		{
			export_one_arg(v, arguments[index]);
			index++;
		}
	}
	return (0);
}
