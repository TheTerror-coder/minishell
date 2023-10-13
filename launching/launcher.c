/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/12 19:30:15 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_launcher(t_vars *v)
{
	if (!strncmp("echo", v->commands->main_command, 5))
	{
		if (v->commands->arguments[1] && strncmp("-n", v->commands->arguments[1], 3) == 0)
			ft_echo(v, 1);
		else
			ft_echo(v, 0);
		return (__TRUE);
	}
	if (!strncmp("cd", v->commands->main_command, 3))
	{
		ft_cd(v);
		return (__TRUE);
	}
	if (!strncmp("pwd", v->commands->main_command, 4))
	{
		ft_pwd( );
		return (__TRUE);
	}
	if (!strncmp("env", v->commands->main_command, 4))
	{
		ft_env(v);
		return (__TRUE);
	}
	if (!strncmp("export", v->commands->main_command, 7))
	{
		ft_export(v, v->argv[1]);
		return (__TRUE);
	}
	if (!strncmp("unset",v->commands->main_command, 6))
	{
		ft_unset(v);
		return (__TRUE);
	}
// ft_putendl_fd("----------------hello---------------", STDERR_FILENO);
	if (!ft_lnch_executable(v))
	{
		return (__FALSE);
	}
	return (__TRUE);
}
