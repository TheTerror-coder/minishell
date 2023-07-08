/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:49:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/08 17:16:08 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_minishell(t_vars *v);

int	main(void)
{
	t_vars	*v;

	v = ft_initvars();
	if (!v)
		return (1);
	ft_minishell(v);
	ft_exitprocss(v, EXIT_SUCCESS);
	return (0);
}

t_bool	ft_minishell(t_vars *v)
{
	v->line = readline("minishell$ ");
	while(v->line && ft_strncmp(v->line, "exit", ft_strlen(v->line)))
	{
		add_history(v->line);
		free(v->line);
		v->line = NULL;
		v->line = readline("minishell$ ");
	}
	free(v->line);
	v->line = NULL;
	return(__TRUE);
}
