/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:49:42 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/30 21:37:12 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_reset_std(t_vars *v);

t_bool	ft_close_tvars(t_vars *v, t_ppex *var)
{
	int		i;
	t_bool	fdbk;

	i = 0;
	fdbk = __TRUE;
	fdbk = ft_fclose(v, &var->pipe_outfd) & fdbk;
	if (var->p)
	{
		while (i < var->nbcmd)
		{
			fdbk = ft_fclose(v, &var->p[i][0]) & fdbk;
			fdbk = ft_fclose(v, &var->p[i][1]) & fdbk;
			i++;
		}
	}
	return (fdbk);
}

t_bool	ft_pcloser(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (!ft_fclose(v, &var->pipe_outfd))
		return (ft_perror(v, EXIT_FAILURE, NULL, __PRINT));
	if (var->i < (var->nbcmd - 1))
	{
		var->pipe_outfd = dup(var->p[var->i][0]);
		if (var->pipe_outfd < 0)
			return (ft_perror(v, EXIT_FAILURE, "dup", __PERROR));
	}
	if (!ft_fclose(v, &var->p[var->i][0]))
		return (ft_perror(v, EXIT_FAILURE, NULL, __PRINT));
	if (!ft_fclose(v, &var->p[var->i][1]))
		return (ft_perror(v, EXIT_FAILURE, NULL, __PRINT));
	if (!ft_reset_std(v))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_reset_std(t_vars *v)
{
	int		prime_stdin;
	int		prime_stdout;

	prime_stdin = -111;
	prime_stdout = -111;
	prime_stdin = dup(v->stdin);
	if (prime_stdin < 0)
		return (ft_perror(v, EXIT_FAILURE, \
				"ft_reset_std(): prime_stdin: dup()", __PERROR));
	prime_stdout = dup(v->stdout);
	if (prime_stdout < 0)
		return (ft_fclose(v, &prime_stdin), ft_perror(v, EXIT_FAILURE, \
				"ft_reset_std(): prime_stdout: dup()", __PERROR));
	if (!ft_ioset_op(v, &prime_stdin, &prime_stdout))
		return (__FALSE);
	return (__TRUE);
}
