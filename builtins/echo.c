/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:22:53 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/18 19:37:03 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_echo(t_vars *v, t_commands *command, t_bool n_option)
{
	int	i;

	i = 1 + n_option;
	if (!ft_set_io(v, command))
		return (__FALSE);
	while (command->arguments[i] != NULL)
	{
		ft_putstr_fd(command->arguments[i], 1);
		i++;
		if (command->arguments[i] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (0);
}
