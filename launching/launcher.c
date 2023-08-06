/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/06 04:44:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_launcher(t_vars *v)
{
	if (!strncmp("echo", v->argv[0], 5))
	{
		if (v->argv[1] && strncmp("-n", v->argv[1], 3) == 0)
			ft_echo(v, 1);
		else
			ft_echo(v, 0);
		return (__TRUE);
	}
	if (!strncmp("cd", v->argv[0], 3))
	{
		ft_cd(v);
		return (__TRUE);
	}
	if (!strncmp("pwd", v->argv[0], 4))
	{
		ft_pwd( );
		return (__TRUE);
	}
	if (!strncmp("env", v->argv[0], 4))
	{
		ft_env(v);
		return (__TRUE);
	}
	if (!strncmp("export", v->argv[0], 7))
	{
		ft_export(v, v->argv[1]);
		return (__TRUE);
	}
	if (!strncmp("unset", v->argv[0], 6))
	{
		ft_unset(v);
		return (__TRUE);
	}
	if (!ft_lnch_executable(v))
	{
		return (__FALSE);
	}
	return (__TRUE);
}
