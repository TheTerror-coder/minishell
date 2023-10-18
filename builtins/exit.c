/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:53:43 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/18 18:09:31 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_exit(t_vars *v, t_commands *command, int status)
{
	if (v->flg_exit_main_procss)
		ft_putendl_fd("exit", STDERR_FILENO);
	if ((command->arguments)[1])
		ft_putendl_fd("minishell: exit: no arguments expected", STDERR_FILENO);
	else
	{
		if (v->flg_exit_main_procss)
			ft_exitmainprocss(v, status);
		else
			ft_exitpipe(v, status);
	}
	return (__TRUE);
}
