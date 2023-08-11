/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargv1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:36:01 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/06 16:54:36 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_parseargv(t_vars *v)
{
	int		fdbk;

	v->jx = 0;
	while (v->argv[v->jx])
	{
		fdbk = ft_redirections(v);
		if (fdbk == __EXIT_REACHED)
			v->jx++;
		else if (!fdbk)
			return (__FALSE);
	}
// int	i;
// i = 0;
// while (v->argv[i])
// {
// 	ft_putendl_fd(v->argv[i], 1);
// 	i++;
// }
// ft_exitprocss(v, EXIT_SUCCESS);
	return (__TRUE);
}

