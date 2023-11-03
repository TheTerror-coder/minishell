/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plumber.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 17:03:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/03 10:24:29 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_plumber(t_vars *v)
{
	char	**my_env;
	t_ppex	*var;

	var = v->var;
	if (!ft_close_tvars(v, v->var))
		ft_exitpipe(v);
	v->flg_exit_main_procss = __FALSE;
	if (ft_run_builtin(v, var->iterator) != __SKIP)
		ft_exitpipe(v);
	ft_freestr(&var->pathcmd);
	var->pathcmd = ft_set_cmdpath(v, var->iterator->main_command);
	if (!var->pathcmd)
		ft_exitpipe(v);
	ft_freesecondaries(v);
	my_env = env_list_to_tab(v);
	if (!my_env && v->my_env->var)
		ft_exitpipe(v);
	execve(var->pathcmd, var->iterator->arguments, my_env);
	perror("ft_plumber(): execve");
	v->exitstatus = __CMD_NOT_EXEC;
	ft_free2str(&my_env);
	ft_exitpipe(v);
	return (__FALSE);
}
