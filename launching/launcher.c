/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/18 15:12:18 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_launcher(t_vars *v)
{
	if (!v->commands->next && ft_run_builtin(v, v->commands) != __SKIP)
		return (__TRUE);
	if (!ft_lnch_executable(v))
		return (__FALSE);
	return (__TRUE);
}

int	ft_run_builtin(t_vars *v, t_commands *command)
{
	if (!v->commands->main_command)
		return (__TRUE);
	if (!strncmp("echo", command->main_command, 5))
	{
		if (command->arguments[1] && strncmp("-n", command->arguments[1], 3) == 0)
			return (ft_echo(command, 1));
		return (ft_echo(command, 0));
	}
	if (!strncmp("cd", command->main_command, 3))
		return (ft_cd(v, command));
	if (!strncmp("pwd", command->main_command, 4))
		return (ft_pwd(command->arguments[1]));
	if (!strncmp("env", command->main_command, 4))
		return (ft_env(v, command));
	if (!strncmp("export", command->main_command, 7))
		return (ft_export(v, command->arguments));
	if (!strncmp("unset", command->main_command, 6))
		return (ft_unset(v, command));
	if (!strncmp("exit", command->main_command, 6))
	{
		ft_exit(v);
		//exit
	}
	return (__SKIP);
}
