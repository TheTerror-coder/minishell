/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:12:23 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/18 15:48:48 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_pwait(t_vars *v, int pid, int option)
{
	int	ret;

	ret = waitpid(pid, &v->status, option);
	if (ret == -1)
		return (ft_goprompt("waitpid", __PERROR));
	if (ret == pid)
		if (WIFEXITED(v->status))
			v->exit_code = WEXITSTATUS(v->status);
	return (__TRUE);
}
