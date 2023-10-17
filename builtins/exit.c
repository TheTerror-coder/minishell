/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:53:43 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/17 23:06:19 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_exit(t_vars *v)
{
	if ((v->commands->arguments)[1])
	{
		ft_putstr_fd("bash: exit: no arguments expected\n", 2);
		return (__FALSE);
	}
	printf("exit\n");
	return (__TRUE);
}
