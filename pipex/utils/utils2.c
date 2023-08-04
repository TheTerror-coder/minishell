/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:16:21 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/03 23:08:22 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_set_cmdlist(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	var->d = 0;
int	i;
	while (var->d < (var->nbcmd))
	{
i = 0;
ft_putnbr_fd(var->nbcmd, 2);
ft_putendl_fd("nbcmd", 2);
ft_putnbr_fd(var->d, 2);
ft_putendl_fd("d", 2);
while (var->cmdlst[var->d][i])
{
ft_putendl_fd("hhihhihihih", 2);
	ft_putendl_fd(var->cmdlst[var->d][i], 2);
	i++;
}
		var->d++;
	}
ft_exitpipe(EXIT_SUCCESS, v);
	

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
