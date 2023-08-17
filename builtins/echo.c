/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:22:53 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/17 00:03:54 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_echo(t_vars *v, t_bool n_option)
{
	int	i;

	i = 1 + n_option;
	while (v->argv[i] != NULL)
	{
		ft_putstr_fd(v->argv[i], 1);
		i++;
		if (v->argv[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (0);
}
