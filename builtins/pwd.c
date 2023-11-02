/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 03:58:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 16:32:53 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_pwd(t_vars *v, char *first_arg)
{
	char	*pwd;

	if (first_arg && first_arg[0] == '-' && first_arg[1] != '\0' \
		&& (first_arg[1] != '-' || first_arg[2] != '\0'))
	{
		ft_putstr_fd("minishell: pwd: no option expected\n", 2);
		v->exitstatus = __BUILTIN_ERROR;
		return (__FALSE);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell: pwd");
		v->exitstatus = EXIT_FAILURE;
		return (__FALSE);
	}
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	v->exitstatus = EXIT_SUCCESS;
	return (__TRUE);
}
