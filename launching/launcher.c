/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:13:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/31 19:02:19 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
