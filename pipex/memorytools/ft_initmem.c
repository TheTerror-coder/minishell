/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initmem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:08:46 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/07 16:16:02 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memtools.h"

void	ft_fdinit(t_vars *var)
{
	var->infile_fd = -111;
	var->outfile_fd = -111;
	var->sp[0] = -111;
	var->sp[1] = -111;
	var->ff = -111;
}

t_bool	ft_init_p(t_vars *var)
{
	int	i;

	i = 0;
	while (i < var->lcmd)
	{
		var->p[i] = ft_calloc(2, sizeof(int));
		if (!var->p[i])
		{
			i--;
			while (i > -1)
			{
				free(var->p[i]);
				var->p[i] = NULL;
				i--;
			}
			free(var->p);
			var->p = NULL;
			return (__FALSE);
		}
		var->p[i][0] = -111;
		var->p[i][1] = -111;
		i++;
	}
	return (__TRUE);
}

t_bool	ft_inittab_int(t_vars *var)
{
	int	i;

	i = 0;
	var->pid = ft_calloc(var->lcmd, sizeof(int));
	if (!var->pid)
		return (__FALSE);
	while (i < var->lcmd)
	{
		var->pid[i] = -111;
		i++;
	}
	var->p = ft_calloc(var->lcmd, sizeof(int *));
	if (!var->p)
		return (__FALSE);
	if (!ft_init_p(var))
		return (__FALSE);
	return (__TRUE);
}

t_vars	*ft_init_tvars(int argc, char **argv)
{
	t_vars	*var;

	var = NULL;
	var = ft_calloc(1, sizeof(t_vars));
	if (!var)
		return (NULL);
	var->awhich = ft_calloc(3, sizeof(char *));
	if (!var->awhich)
		return (NULL);
	var->heredoc_flg = __FALSE;
	var->infile_flg = __TRUE;
	var->limiter = NULL;
	var->argc = argc;
	var->argv = argv;
	ft_fdinit(var);
	return (var);
}
/*
// t_bool	ft_initoutfl(t_vars *var)
// {
// 	var->outfile_fd = open(var->argv[var->argc - 1], \
// 							O_CREAT | O_WRONLY, __S_OPERM);
// 	if (var->outfile_fd == -1)
// 		return (ft_perror(var, EXIT_FAILURE, \
// 				var->argv[var->argc - 1], __PERROR));
// 	return (ft_fclose(&var->outfile_fd));
// }
*/