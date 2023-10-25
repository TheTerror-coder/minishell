/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iosetter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:13:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/25 19:16:31 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_io_firstcmnd(t_vars *v);
t_bool	ft_io_cmnd(t_vars *v);
t_bool	ft_io_lastcmnd(t_vars *v);

t_bool	ft_ioset(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (var->i == 0)
		return (ft_io_firstcmnd(v));
	else if (var->i < (var->nbcmd - 1))
		return (ft_io_cmnd(v));
	else
		return (ft_io_lastcmnd(v));
	return (__TRUE);
}

t_bool	ft_io_firstcmnd(t_vars *v)
{
	t_ppex	*var;
	int		prime_stdin;

	var = v->var;
	prime_stdin = -111;
	prime_stdin = dup(v->stdin);
	if (prime_stdin < 0)
		return (ft_perror(EXIT_FAILURE, "ft_io_firstcmnd(): prime_stdin: dup()", __PERROR));
	if (!ft_ioset_op(&prime_stdin, &var->p[0][1]))
		return (__FALSE);
	if (!ft_set_io(v, var->iterator))
		return (var->skip_command_flg = __TRUE, __FALSE);
	return (__TRUE);
}

t_bool	ft_io_cmnd(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (!ft_ioset_op(&var->pipe_outfd, &var->p[var->i][1]))
		return (__FALSE);
	if (!ft_set_io(v, var->iterator))
		return (var->skip_command_flg = __TRUE, __FALSE);
	return (__TRUE);
}

t_bool	ft_io_lastcmnd(t_vars *v)
{
	t_ppex	*var;
	int		prime_stdout;

	var = v->var;
	prime_stdout = dup(v->stdout);
	if (prime_stdout < 0)
		return (ft_perror(EXIT_FAILURE, "ft_io_lastcmnd(): prime_stdout: dup()", __PERROR));
	if (!ft_ioset_op(&var->pipe_outfd, &prime_stdout))
		return (__FALSE);
	if (!ft_set_io(v, var->iterator))
		return (var->skip_command_flg = __TRUE, __FALSE);
	return (__TRUE);
}
