/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:49:42 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/07 16:16:21 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memtools.h"

t_bool	ft_fclose(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
			return (__FALSE);
		*fd = -111;
	}
	return (__TRUE);
}

t_bool	ft_close_tvars(t_vars *var)
{
	int		i;
	t_bool	fdbk;

	i = 0;
	fdbk = __TRUE;
	fdbk = ft_fclose(&var->infile_fd) & fdbk;
	fdbk = ft_fclose(&var->outfile_fd) & fdbk;
	fdbk = ft_fclose(&var->sp[0]) & fdbk;
	fdbk = ft_fclose(&var->sp[1]) & fdbk;
	if (var->p)
	{
		while (i < var->lcmd)
		{
			fdbk = ft_fclose(&var->p[i][0]) & fdbk;
			fdbk = ft_fclose(&var->p[i][1]) & fdbk;
			i++;
		}
	}
	fdbk = ft_fclose(&var->ff) & fdbk;
	return (fdbk);
}

t_bool	ft_pcloser(t_vars *var)
{
	if (!ft_fclose(&var->ff))
		return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
	var->ff = dup(var->p[var->i][0]);
	if (var->ff == -1)
		return (ft_perror(var, EXIT_FAILURE, "dup p[0]", __PERROR));
	if (!ft_fclose(&var->p[var->i][0]))
		return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
	if (!ft_fclose(&var->p[var->i][1]))
		return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
	return (__TRUE);
}
