/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/16 14:58:25 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_bool	ft_prompt(t_vars *v)
{
	v->line = readline("minishell$ ");
// ft_putnbr_fd(ft_strlen(v->line), 1);
	while(!ft_strlen(v->line) || ft_strncmp(v->line, "exit", ft_strlen(v->line)))
	{
		add_history(v->line);
// ft_putendl_fd("hello", 1);
		ft_minishell(v);
		free(v->line);
		v->line = NULL;
		v->line = readline("minishell$ ");
	}
	free(v->line);
	v->line = NULL;
	return(__TRUE);
}

t_bool	ft_minishell(t_vars *v)
{
	if (!ft_lmanager(v))
		return (__FALSE);
	if (!ft_launcher(v))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_lmanager(t_vars *v)
{
	ft_checkessentials(v);
	if (!ft_setargv(v))
		return (__FALSE);
	// ft_cmdidentity(v);
	return (__TRUE);
}
