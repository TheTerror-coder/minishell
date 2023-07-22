/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/22 05:24:18 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_launcher(t_vars *v)
{
	if (!strncmp("echo", v->argv[0], 5))
	{
		if (v->argv[1] != NULL && strncmp("-n", v->argv[1], 3) == 0)
			ft_echo(v, 0);
		else
			ft_echo(v, 1);
		return (__TRUE);
	}
	if (!strncmp("cd", v->argv[0], 3))
	{
		ft_cd(v->argv[1]);
		return (__TRUE);
	}
	ft_lnch_executable(v);
	return (__TRUE);
}
