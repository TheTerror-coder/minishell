/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:15:53 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/11 13:20:46 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exitstatus = EXIT_SUCCESS;

int	main(int argc, char **argv, char **envp)
{
	t_vars	*v;

	(void) argc;
	(void) argv;
	v = ft_initvars();
	if (!v)
		return (EXIT_FAILURE);
	v->envp = envp;
	if (!ft_setenv(v))
	{
		perror("minishell: ft_setenv");
		return (0);
	}
	if (!ft_setpath2(v))
		ft_exitprocss(v, exitstatus);
	ft_prompt(v);
	ft_exitprocss(v, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
