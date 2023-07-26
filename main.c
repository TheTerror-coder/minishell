/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:15:53 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/26 06:49:15 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_vars	*v;

	(void) argc;
	(void) argv;
	v = ft_initvars();
	if (!v)
		return (1);
	v->envp = envp;
	ft_set_pwd(v);
	ft_setenv(v);
	ft_setpath(v);
	ft_prompt(v);
	ft_exitprocss(v, EXIT_SUCCESS);
	return (0);
}
