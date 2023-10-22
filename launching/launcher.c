/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/22 17:53:11 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	launch_right_builtin(t_vars *v, t_commands *command);

t_bool	ft_launcher(t_vars *v)
{
	int	fdbk;

	fdbk = __TRUE;
	if (!ft_run_heredocs(v, v->commands))
		return (__TRUE);
	if (!v->commands->next)
	{
		v->flg_exit_main_procss = __TRUE;
		fdbk = ft_run_builtin(v, v->commands);
		if (fdbk != __SKIP)
			return (fdbk && 1);
	}
	if (!ft_lnch_executable(v))
		return (__FALSE);
	return (__TRUE);
}


int	ft_run_builtin(t_vars *v, t_commands *command)
{
	if (!command->main_command)
		return (__SKIP);
	if (!ft_strncmp("echo", command->main_command, 5) || \
		!ft_strncmp("cd", command->main_command, 3) || \
		!ft_strncmp("pwd", command->main_command, 4) || \
		!ft_strncmp("env", command->main_command, 4) || \
		!ft_strncmp("export", command->main_command, 7) || \
		!ft_strncmp("unset", command->main_command, 6) || \
		!ft_strncmp("exit", command->main_command, 6))
		return (launch_right_builtin(v, command));
	return (__SKIP);
}

t_bool	launch_right_builtin(t_vars *v, t_commands *command)
{
	if (!ft_set_io(v, command))
		return (__FALSE);
	if (!ft_strncmp("echo", command->main_command, 5))
	{
		if (command->arguments[1] && strncmp("-n", command->arguments[1], 3) == 0)
			return (ft_echo(command, 1));
		return (ft_echo(command, 0));
	}
	if (!ft_strncmp("cd", command->main_command, 3))
		return (ft_cd(v, command));
	if (!ft_strncmp("pwd", command->main_command, 4))
		return (ft_pwd(command->arguments[1]));
	if (!ft_strncmp("env", command->main_command, 4))
		return (ft_env(v, command));
	if (!ft_strncmp("export", command->main_command, 7))
		return (ft_export(v, command, command->arguments));
	if (!ft_strncmp("unset", command->main_command, 6))
		return (ft_unset(v, command));
	else
		return (ft_exit(v, command));
}
