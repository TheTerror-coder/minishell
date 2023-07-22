/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/22 03:35:14 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_launcher(t_vars *v)
{
	if (!strncmp("echo", v->argv[0], 5))
	{
		ft_echo(v, 0);
		return (__TRUE);
	}
	ft_lnch_executable(v);
	return (__TRUE);
}
