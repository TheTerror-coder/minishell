/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:22:53 by lmohin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/10/27 02:32:42 by lmohin           ###   ########.fr       */
=======
/*   Updated: 2023/10/26 21:43:18 by TheTerror        ###   ########lyon.fr   */
>>>>>>> c456bc4 (update exit code status)
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	is_n_flag(char	*s)
{
	size_t	i;

	if (!s)
		return (__FALSE);
	if (s[0] != '-')
		return (__FALSE);
	if (s[1] != 'n')
		return (__FALSE);
	i = 2;
	while (s[i] != '\0')
	{
		if (s[i] != 'n')
			return (__FALSE);
		i++;
	}
	return (__TRUE);
}

t_bool	ft_echo(t_commands *command)
{
	t_bool	n_flag;
	size_t	i;

	i = 1;
	n_flag = is_n_flag(command->arguments[1]);
	while (is_n_flag(command->arguments[i]))
		i++;
	while (command->arguments[i] != NULL)
	{
		ft_putstr_fd(command->arguments[i], STDOUT_FILENO);
		i++;
		if (command->arguments[i] != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
<<<<<<< HEAD
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	exitstatus = 0;
=======
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	exitstatus = EXIT_SUCCESS;
>>>>>>> c456bc4 (update exit code status)
	return (__TRUE);
}
