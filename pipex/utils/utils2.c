/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:16:21 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:02:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_setcmd(t_vars *v);

t_bool	ft_set_cmdlist(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	var->d = 1;
	var->cmdlst = ft_calloc(var->argc, sizeof(char *));
	if (!var->cmdlst)
		return (__FALSE);
int	i;
	while (var->d < (var->argc))
	{
		if (var->argv[var->d][0] == 0)
			var->cmdlst[var->lcmd] = NULL;
		else
		{
			if (!ft_setcmd(v))
				return (__FALSE);
		}
i = 0;
while (var->cmdlst[var->lcmd][i])
{
	ft_putendl_fd(var->cmdlst[var->lcmd][i], 2);
	i++;
}
		var->d++;
		var->lcmd++;
	}
ft_exitpipe(EXIT_SUCCESS, v);
	if (!ft_inittab_int(var))
		return (__FALSE);

// ft_putnbr_fd(var->argc, 2);
// ft_putendl_fd("argc", 2);
// ft_putnbr_fd(var->lcmd, 2);
// ft_putendl_fd("len", 2);
	return (__TRUE);
}

t_bool	ft_fwait(t_vars *v, int pid, int option)
{
	t_ppex	*var;
	int	ret;

	var = v->var;
	ret = waitpid(pid, &var->status, option);
	if (ret == -1)
		return (ft_perror(v, EXIT_FAILURE, "waitpid", __PERROR));
	if (ret == pid)
		if (WIFEXITED(var->status))
			var->exit = WEXITSTATUS(var->status);
	return (__TRUE);
}
