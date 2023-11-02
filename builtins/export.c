/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 04:55:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 17:49:03 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	compare_str_and_var(char *env_var, char *str);

char	*get_var_name(t_vars *v, char *str)
{
	char	*var;
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	var = ft_substr(str, 0, i);
	if (!var)
		return (ft_leave(v, EXIT_FAILURE, "ft_substr", __PERROR), NULL);
	return (var);
}

t_bool	find_var(t_vars *v, char *var, char *str)
{
	t_env	*tmp;

	tmp = v->my_env;
	while (tmp->next && !compare_str_and_var(tmp->var, var))
		tmp = tmp->next;
	if (!compare_str_and_var(tmp->var, var))
		return (add_env_var(v, str));
	else
	{
		if (str[ft_strlen(var)] == '=')
		{
			free(tmp->var);
			tmp->var = ft_strdup(str);
			if (!tmp->var)
			{
				ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR);
				return (__FALSE);
			}
		}
	}
	return (__TRUE);
}

t_bool	check_var_name_format(char *str)
{
	size_t	i;

	if ((str[0] <= '9' && str[0] >= '0') || str[0] == '\0')
		return (__FALSE);
	i = 0;
	while (str[i] != '=' && str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (__FALSE);
		i++;
	}
	return (__TRUE);
}

t_bool	export_one_arg(t_vars *v, char *str)
{
	char	*var;

	if (str[0] == '=')
		return (print_not_valid_identifier(v, str));
	var = get_var_name(v, str);
	if (!var)
		return (__FALSE);
	if (!check_var_name_format(var))
	{
		print_not_valid_identifier(v, var);
		return (free(var), __TRUE);
	}
	if (!v->my_env->var)
	{
		v->my_env->var = ft_strdup(str);
		if (!v->my_env->var)
		{
			ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR);
			return (free(var), __FALSE);
		}
		return (free(var), __TRUE);
	}
	if (!find_var(v, var, str))
		return (free(var), __FALSE);
	return (free(var), __TRUE);
}

t_bool	ft_export(t_vars *v, t_commands *command, char **arguments)
{
	int	index;

	(void) command;
	v->exitstatus = 0;
	if (!arguments[1] || !ft_strncmp(arguments[1], "--", 3))
		return (print_export(v));
	if (arguments[1][0] == '-' && arguments[1][1] != '\0')
	{
		v->exitstatus = 2;
		ft_putstr_fd("minishell: export: no option expected\n", 2);
		return (__FALSE);
	}
	else
	{
		index = 1;
		while (arguments[index])
		{
			if (!export_one_arg(v, arguments[index]))
				return (__FALSE);
			index++;
		}
	}
	if (v->exitstatus != 0)
		return (__FALSE);
	return (__TRUE);
}
