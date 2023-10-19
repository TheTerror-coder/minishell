/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 03:58:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/19 21:51:41 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_pwd(t_vars *v, t_commands *command, char *first_arg)
{
	char	*pwd;

	if (first_arg && first_arg[0] == '-' && first_arg[1] != '\0' \
		&& (first_arg[1] != '-' || first_arg[2] != '\0'))
	{
		ft_putstr_fd("minishell: ft_pwd: no option available\n", 2);
		return (0);
	}
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		perror("minishell: ft_pwd");
	free(pwd);
	return (1);
}
