/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:16:21 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/29 21:09:13 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_fwait(t_vars *v, int pid, int option)
{
	t_ppex	*var;
	int	ret;

	var = v->var;
	ret = waitpid(pid, &var->code, option);
	if (ret == -1)
		return (ft_perror(v, EXIT_FAILURE, "waitpid", __PERROR));
	if (ret == pid)
		if (WIFEXITED(var->code))
			v->exitstatus = WEXITSTATUS(var->code);
	return (__TRUE);
}
