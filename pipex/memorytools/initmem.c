/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initmem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:08:46 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:02:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_fdinit(t_ppex *var)
{
	var->infile_fd = dup(STDIN_FILENO);
	var->outfile_fd = dup(STDOUT_FILENO);
	if (var->infile_fd == -1 || var->outfile_fd == -1)
		return (perror("dup"), __FALSE);
	var->sp[0] = -111;
	var->sp[1] = -111;
	var->ff = -111;
	return (__TRUE);
}

t_bool	ft_init_p(t_ppex *var)
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

t_bool	ft_inittab_int(t_ppex *var)
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

t_ppex	*ft_init_tvars(int argc, char **argv)
{
	t_ppex	*var;

	var = NULL;
	var = ft_calloc(1, sizeof(t_ppex));
	if (!var)
		exit(EXIT_FAILURE);
	var->argc = argc;
	var->argv = argv;
	if (!ft_fdinit(var))
		return (NULL);
	return (var);
}
