/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:15:53 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/01 14:19:40 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_global;

int	main(int argc, char **argv, char **envp)
{
	t_vars	*v;

	(void) argv;
	if (argc > 1)
	{
		ft_leave(NULL, EXIT_FAILURE, \
			"minishell takes no arguments or options", __PRINT);
		return (EXIT_FAILURE);
	}
	v = ft_initvars();
	if (!v)
		return (EXIT_FAILURE);
	if (!ft_setenv(v, envp))
		ft_exitmainprocss(v, EXIT_FAILURE);
	ft_prompt(v);
	ft_exitmainprocss(v, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
