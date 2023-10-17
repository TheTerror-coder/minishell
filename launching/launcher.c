/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/17 23:04:11 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_launcher(t_vars *v)
{
	if (!ft_run_builtin(v))
		return (__FALSE);
	if (!ft_lnch_executable(v))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_run_builtin(t_vars *v)
{
	if (!v->commands->main_command)
		return (__TRUE);
	if (!strncmp("echo", v->commands->main_command, 5))
	{
		if (v->commands->arguments[1] && strncmp("-n", v->commands->arguments[1], 3) == 0)
			return (ft_echo(v, 1));
		return (ft_echo(v, 0));
	}
	if (!strncmp("cd", v->commands->main_command, 3))
		return (ft_cd(v));
	if (!strncmp("pwd", v->commands->main_command, 4))
	{
		ft_pwd(v->commands->arguments[1]);
		return (__TRUE);
	}
	if (!strncmp("env", v->commands->main_command, 4))
		return (ft_env(v));
	if (!strncmp("export", v->commands->main_command, 7))
		return (ft_export(v, v->commands->arguments));
	if (!strncmp("unset",v->commands->main_command, 6))
		return (ft_unset(v));
	if (!strncmp("exit", v->commands->main_command, 6))
	{
		return (ft_exit(v));
		/* if ft_exit(v)
			exitprocess */
	}
	return (__TRUE);
}
