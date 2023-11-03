/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/03 14:27:20 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_minishell(t_vars *v);

t_bool	ft_prompt(t_vars *v)
{
	set_readline_signals();
	v->line = readline("minishell$ ");
	while (v->line)
	{
		if ((v->line)[0])
			add_history(v->line);
		ft_minishell(v);
		ft_clear_created_tempfiles(v);
		if ((v->line)[0])
			ft_freecommands(v);
		ft_raz(v);
		ft_freestr(&v->line);
		v->line = readline("minishell$ ");
	}
	ft_freestr(&v->line);
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (__TRUE);
}

t_bool	ft_minishell(t_vars *v)
{
	v->commands = get_commands(v);
	if (!v->commands)
		return (__FALSE);
	if (v->flg_parsing_is_ok == __FALSE)
		return (__FALSE);
	if (!ft_launcher(v))
		return (__FALSE);
	return (__TRUE);
}
