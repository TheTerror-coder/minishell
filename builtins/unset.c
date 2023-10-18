/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 04:06:37 by marvin            #+#    #+#             */
/*   Updated: 2023/10/18 19:11:53 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_var_name(char *var)
{
	int	i;

	i = 0;
	if (var[0] != '\0' && !ft_isalpha(var[0]) && var[0] != '_')
	{
		ft_putstr_fd("minishell: ft_unset: `", 1);
		ft_putstr_fd(var, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		return (__FALSE);
	}
	i++;
	while (var[i] != '\0')
	{
		if (!ft_isalpha(var[i]) && !isalnum(var[i]) && var[i] != '_')
		{
			ft_putstr_fd("minishell: ft_unset: `", 1);
			ft_putstr_fd(var, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			return (__FALSE);
		}
		i++;
	}
	return (__TRUE);
}

t_bool	find_and_unset_var(t_vars *v, char *var)
{
	t_env	*tmp;
	t_env	*post_tmp;
	char	*var_equal;
	size_t	length_var;

	length_var = ft_strlen(var) + 1;
	var_equal = ft_strjoin(var, "=");
	if (!var_equal)
		return (__FALSE);
	post_tmp = v->my_env;
	tmp = (v->my_env)->next;
	if (!ft_strncmp(tmp->var, var_equal, length_var))
	{
		free(v->my_env);
		free(v->my_env);
		v->my_env = tmp;
		return (__TRUE);
	}
	while (tmp->next && ft_strncmp(tmp->var, var_equal, length_var))
	{
		post_tmp = tmp;
		tmp = tmp->next;
	}
	if (!ft_strncmp(tmp->var, var_equal, length_var))
	{
		free(tmp->var);
		post_tmp->next = tmp->next;
		free(tmp);
	}
	free(var_equal);
	return (__TRUE);
}

t_bool	ft_unset(t_vars *v, t_commands *command)
{
	int		i;
	char	**argv;

	if (!ft_set_io(v, command))
		return (__FALSE);
	argv = command->arguments;
	i = 1;
	while (argv[i])
	{
		if (check_var_name(argv[i]))
			find_and_unset_var(v, argv[i]);
		i++;
	}
	return (__TRUE);
}
