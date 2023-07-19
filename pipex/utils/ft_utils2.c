/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:16:21 by TheTerror         #+#    #+#             */
/*   Updated: 2023/06/07 17:28:57 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

t_bool	ft_set_cmdlist(t_vars *var)
{
	int	i;

	i = 2;
	if (var->heredoc_flg)
		i = 3;
	var->cmdlst = ft_calloc(var->argc - i, sizeof(char *));
	if (!var->cmdlst)
		return (__FALSE);
	while (i < (var->argc - 1))
	{
		if (var->argv[i][0] == 0)
			var->cmdlst[var->lcmd] = NULL;
		else
		{
			var->cmdlst[var->lcmd] = ft_split(var->argv[i], ' ');
			if (!var->cmdlst[var->lcmd])
				return (__FALSE);
		}
		i++;
		var->lcmd++;
	}
	if (!ft_inittab_int(var))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_fwait(t_vars *var, int pid, int option)
{
	int	ret;

	ret = waitpid(pid, &var->status, option);
	if (ret == -1)
		return (ft_perror(var, EXIT_FAILURE, "waitpid", __PERROR));
	if (ret == pid)
		if (WIFEXITED(var->status))
			var->exit = WEXITSTATUS(var->status);
	return (__TRUE);
}

/*
t_bool	ft_setwch(t_vars *var)
{
	if (var->awhich[0])
		free(var->awhich[0]);
	var->awhich[0] = ft_strdup("which");
	if (!var->awhich[0])
		return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
	if (var->awhich[1])
		free(var->awhich[1]);
	var->awhich[1] = ft_strdup(var->cmdlst[var->i][0]);
	if (!var->awhich[1])
		return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
	return (__TRUE);
}
*/
