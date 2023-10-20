/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 04:06:37 by marvin            #+#    #+#             */
/*   Updated: 2023/10/20 03:14:25 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_var_name(char *var)
{
	size_t	i;

	i = 0;
	if (var[0] != '\0' && !ft_isalpha(var[0]) && var[0] != '_')
	{
		ft_putstr_fd("minishell: ft_unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		exitstatus = 1;
		return (__FALSE);
	}
	i++;
	while (var[i] != '\0')
	{
		if (!ft_isalpha(var[i]) && !isalnum(var[i]) && var[i] != '_')
		{
			ft_putstr_fd("minishell: ft_unset: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exitstatus = 2;
			return (__FALSE);
		}
		i++;
	}
	return (__TRUE);
}

t_bool	find_and_unset_arg(t_vars *v, char *arg_equal, size_t length_arg)
{
	t_env	*env_next;
	t_env	*post_tmp;

	post_tmp = v->my_env;
	env_next = (v->my_env)->next;
	if (!ft_strncmp(env_next->var, arg_equal, length_arg))
	{
		free(v->my_env);
		free(arg_equal);
		v->my_env = env_next;
		return (__TRUE);
	}
	while (env_next->next && ft_strncmp(env_next->var, arg_equal, length_arg))
	{
		post_tmp = env_next;
		env_next = env_next->next;
	}
	if (!ft_strncmp(env_next->var, arg_equal, length_arg))
	{
		free(env_next->var);
		post_tmp->next = env_next->next;
		free(env_next);
	}
	free(arg_equal);
	return (__TRUE);
}

t_bool	unset_one_arg(t_vars *v, char *arg)
{
	char	*arg_equal;

	if (check_var_name(arg))
	{
		arg_equal = ft_strjoin(arg, "=");
		if (!arg_equal)
		{
			perror("minishell: ft_unset: ");
			exitstatus = 1;
			return (__FALSE);
		}
		find_and_unset_arg(v, arg_equal, ft_strlen(arg_equal));
	}
	return (__TRUE);
}

t_bool	ft_unset(t_vars *v, t_commands *command)
{
	size_t		i;

	exitstatus = 0;
	i = 1;
	while (command->arguments[i])
	{
		if (!unset_one_arg(v, command->arguments[i]) && exitstatus == 1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
