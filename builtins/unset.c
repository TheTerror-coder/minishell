/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 04:06:37 by marvin            #+#    #+#             */
/*   Updated: 2023/10/29 09:01:59 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_var_name(char *var)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		ft_putstr_fd("minishell: ft_unset: `", STDERR_FILENO);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		exitstatus = EXIT_FAILURE;
		return (__FALSE);
	}
	i++;
	while (var[i] != '\0')
	{
		if (!ft_isalpha(var[i]) && !ft_isalnum(var[i]) && var[i] != '_')
		{
			ft_putstr_fd("minishell: ft_unset: `", STDERR_FILENO);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			exitstatus = EXIT_FAILURE;
			return (__FALSE);
		}
		i++;
	}
	return (__TRUE);
}

t_bool	find_and_unset_arg(t_vars *v, char *arg_equal, size_t length_arg)
{
	t_env	*env_tmp;
	t_env	*env_previous;

	env_tmp = (v->my_env)->next;
	env_previous = v->my_env;
	if (!ft_strncmp(v->my_env->var, arg_equal, length_arg))
	{
		free(v->my_env->var);
		free(arg_equal);
		if (v->my_env->next)
			v->my_env = v->my_env->next;
		else
		{
			v->my_env->next = NULL;
			v->my_env->var = NULL;
		}
		return (__TRUE);
	}
	while (env_tmp && ft_strncmp(env_tmp->var, arg_equal, length_arg))
	{
		env_previous = env_tmp;
		env_tmp = env_tmp->next;
	}
	if (env_tmp)
	{
		free(env_tmp->var);
		env_previous->next = env_tmp->next;
		free(env_tmp);
	}
	free(arg_equal);
	return (__TRUE);
}

t_bool	unset_one_arg(t_vars *v, char *arg)
{
	char	*arg_equal;

	if (check_var_name(arg))
	{
		if (v->my_env == NULL)
			return (__TRUE);
		arg_equal = ft_strjoin(arg, "=");
		if (!arg_equal)
		{
			perror("minishell: ft_unset: ");
			exitstatus = EXIT_FAILURE;
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
	if (command->arguments[1] && command->arguments[1][0] == '-' \
		&& command->arguments[1][1] != '\0')
	{
		exitstatus = __BUILTIN_ERROR;
		ft_putstr_fd("minishell: ft_unset: no option expected\n", \
			STDERR_FILENO);
		return (__FALSE);
	}
	while (command->arguments[i])
	{
		if (!unset_one_arg(v, command->arguments[i]) && exitstatus == 1)
			return (__FALSE);
		i++;
	}
	return (__TRUE);
}
