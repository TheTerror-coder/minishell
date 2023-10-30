/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 04:26:44 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/30 10:09:07 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	get_old_env(t_vars *v, char **envp);
t_bool	set_pwd(t_vars *v);
t_bool	add_env_var(t_vars *v, char *var);
void	add_to_end_of_env(t_env *env, t_env *new);

t_bool	ft_setenv(t_vars *v, char **envp)
{
	if ((envp[0]) && !get_old_env(v, envp))
		return (free_env(v), __FALSE);
	if (!set_pwd(v))
		return (free_env(v), __FALSE);
	return (__TRUE);
}

t_bool	get_old_env(t_vars *v, char **envp)
{
	size_t	i;

	v->my_env->var = ft_strdup(envp[0]);
	if (!(v->my_env->var))
		return (ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR), __FALSE);
	i = 1;
	while (envp[i])
	{
		if (!add_env_var(v, envp[i]))
			return (__FALSE);
		i++;
	}
	return (__TRUE);
}

t_bool	set_pwd(t_vars *v)
{
	char	*pwd;
	char	*env_pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_leave(v, EXIT_FAILURE, "getcwd", __PERROR), __FALSE);
	env_pwd = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!env_pwd)
		return (ft_leave(v, EXIT_FAILURE, "ft_strjoin", __PERROR), __FALSE);
	if (!export_one_arg(v, env_pwd))
		return (free(env_pwd), __FALSE);
	return (free(env_pwd), __TRUE);
}

t_bool	add_env_var(t_vars *v, char *var)
{
	t_env	*new;

	if (!v->my_env->var)
	{
		v->my_env->var = ft_strdup(var);
		if (!(v->my_env->var))
			return (ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR), __FALSE);
		return (__TRUE);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (ft_leave(v, EXIT_FAILURE, "malloc", __PERROR), __FALSE);
	new->next = NULL;
	new->var = ft_strdup(var);
	if (!(new->var))
	{
		free(new);
		return (ft_leave(v, EXIT_FAILURE, "ft_strdup", __PERROR), __FALSE);
	}
	add_to_end_of_env(v->my_env, new);
	return (__TRUE);
}

void	add_to_end_of_env(t_env *env, t_env *new)
{
	while (env->next != NULL)
		env = env->next;
	env->next = new;
}
