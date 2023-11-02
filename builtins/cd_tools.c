/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:11:20 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/02 16:46:31 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	check_cd_options(t_vars *v, char *first_arg)
{
	if (first_arg && first_arg[0] == '-' && first_arg[1] != '\0' \
		&& (first_arg[1] != '-' || first_arg[2] != '\0'))
	{
		ft_putstr_fd("minishell: cd: no option expected\n", 2);
		v->exitstatus = __BUILTIN_ERROR;
		return (__FALSE);
	}
	return (__TRUE);
}

t_bool	print_chdir_error(t_vars *v, char *old_pwd, t_commands *command)
{
	free(old_pwd);
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(command->arguments[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror(NULL);
	return (v->exitstatus = EXIT_FAILURE, __FALSE);
}

t_bool	do_chdir(t_vars *v, char *var)
{
	char	*message_to_print;

	if (chdir(var) == -1)
	{
		message_to_print = ft_strjoin("minishell: cd: ", var);
		if (message_to_print)
			perror(message_to_print);
		else
			perror("minishell: chdir ");
		free(message_to_print);
		return (v->exitstatus = EXIT_FAILURE, __FALSE);
	}
	return (__TRUE);
}
