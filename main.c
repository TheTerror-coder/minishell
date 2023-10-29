/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:15:53 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/29 02:50:34 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exitstatus = EXIT_SUCCESS;

int	main(int argc, char **argv, char **envp)
{
	t_vars	*v;

	(void) argv;
	if (argc > 1)
	{
		ft_leave(EXIT_FAILURE, \
			"minishell takes no arguments or options", __PRINT);
		return (exitstatus);
	}
	v = ft_initvars();
	if (!v)
		return (exitstatus);
	if (!ft_setenv(v, envp))
	{
		close(v->stdin);
		close(v->stdout);
		free(v);	
		return (EXIT_FAILURE);
	}
	ft_prompt(v);
	ft_exitmainprocss(v, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
