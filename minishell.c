/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/17 00:30:39 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool ft_prompt(t_vars *v)
{
	
	v->line = readline("minishell$ ");
// ft_putnbr_fd(ft_strlen(v->line), 1);
// ft_putendl_fd("hello", 1);
	while (!ft_strlen(v->line) || ft_strncmp(v->line, "exit", ft_strlen(v->line) + 5))
	{
		ft_razflags(v);
		if ((v->line)[0])
			add_history(v->line);
		ft_minishell(v);
		ft_freestr(&v->line);
		v->line = readline("minishell$ ");
	}
	ft_freestr(&v->line);
	return (__TRUE);
}

t_bool ft_minishell(t_vars *v)
{
	if (!ft_lmanager(v))
		return (__FALSE);
	if (!ft_launcher(v))
		return (__FALSE);
	return (__TRUE);
}

t_bool ft_lmanager(t_vars *v)
{
	if (!ft_setargv(v))
		return (__FALSE);
	if (!ft_parseargv(v))
		return (__FALSE);
	if (v->flg_pipeline)
		if (!ft_setpipeline(v))
			return (__FALSE);
	return (__TRUE);
}
