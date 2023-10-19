/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:53:43 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/20 00:17:06 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_exit(t_vars *v, t_commands *command, int status)
{
	if (v->flg_exit_main_procss)
		ft_putendl_fd("exit", STDERR_FILENO);
	if ((command->arguments)[1])
	{
		exitstatus = 2;
		ft_putendl_fd("minishell: exit: no arguments expected", STDERR_FILENO);
	}
	else
	{
		exitstatus = 0;
		if (v->flg_exit_main_procss)
			ft_exitmainprocss(v, status);
		else
			ft_exitpipe(v, status);
	}
	return (__TRUE);
}
