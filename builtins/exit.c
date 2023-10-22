/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:53:43 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/22 18:27:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_arg_is_numeric(t_vars *v, t_commands *command);
void	ft_exit_op(t_vars *v);

t_bool	ft_exit(t_vars *v, t_commands *command)
{
	if (v->flg_exit_main_procss)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (!command->arguments[1])
		ft_exit_op(v);
	ft_arg_is_numeric(v, command);
	if (ft_2strlen(command->arguments) > 2)
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	else
	{
		exitstatus = (char) ft_atoi(command->arguments[1]);
		ft_exit_op(v);
	}
	return (exitstatus = EXIT_FAILURE, __FALSE);
}

t_bool	ft_arg_is_numeric(t_vars *v, t_commands *command)
{
	int	i;

	i = 0;
	while (is_whitespace(command->arguments[1][i]))
		i++;
	if (command->arguments[1][i] == '+' || command->arguments[1][i] == '-')
		i++;
	while (command->arguments[1][i] && ft_isdigit(command->arguments[1][i]))
		i++;
	while (is_whitespace(command->arguments[1][i]))
		i++;
	if (i == 0 || command->arguments[1][i])
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(command->arguments[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exitstatus = __BUILTIN_ERROR;
		ft_exit_op(v);
	}
	return (__FALSE);
}

void	ft_exit_op(t_vars *v)
{
	if (v->flg_exit_main_procss)
		ft_exitmainprocss(v, exitstatus);
	else
		ft_exitpipe(v);
}
