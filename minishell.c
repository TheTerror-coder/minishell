/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/16 22:27:08 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool ft_prompt(t_vars *v)
{
	v->line = readline("minishell$ ");
	while (!ft_strlen(v->line) || ft_strncmp(v->line, "exit", 5))
	{
		// ft_razflags(v);
		if ((v->line)[0])
			add_history(v->line);
		ft_minishell(v);
		ft_clear_created_tempfiles(v);
		ft_freestr(&v->line);
		v->line = readline("minishell$ ");
	}
	ft_freestr(&v->line);
	return (__TRUE);
}

t_bool ft_minishell(t_vars *v)
{
	char	**args;

	args = NULL;
	args = ft_splitwset(v->line, " \t");
	if (!args || !args[0])
		return (__TRUE);
	v->commands = get_commands(v);

// t_commands	*it = v->commands;
// while (it)
// {
// 	ft_putendl_fd("---------------Main command-----------", STDERR_FILENO);
// 	ft_putendl_fd(it->main_command, STDERR_FILENO);
// 	int	i = 0;
// 	ft_putendl_fd("---------------arguments-----------", STDERR_FILENO);
// 	while (it->arguments[i])
// 	{
// 		ft_putendl_fd(it->arguments[i], STDERR_FILENO);
// 		i++;
// 	}
// 	ft_putendl_fd("---------------remaining tokens-----------", STDERR_FILENO);
// t_token	*it1 = it->tokens;
// while (it1)
// {
// 	ft_putendl_fd(it1->content, STDERR_FILENO);
// 	it1 = it1->next;
// }
// it = it->next;
// }
// ft_exitmainprocss(v , EXIT_FAILURE);
	if (!ft_launcher(v))
		return (__FALSE);
	return (__TRUE);
}
