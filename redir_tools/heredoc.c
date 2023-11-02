/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:53:24 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/02 14:21:39 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_heredoc2(t_vars *v);
void	ft_heredoc_op1(t_vars *v);
void	ft_heredoc_op2(t_vars *v);
void	ft_signal_terminate(t_vars *v);

t_bool	ft_heredoc(t_vars *v)
{
	int	pid;

	pid = -1;
	if (!ft_fclose(v, &v->hdoc_fd))
		return (__FALSE);
	if (!ft_openatemp(v))
		return (__FALSE);
	pid = fork();
	if (pid < 0)
		return (ft_leave(v, EXIT_FAILURE, "fork", __PERROR));
	if (pid == 0)
	{
		heredoc_signals();
		ft_heredoc_op1(v);
	}
	ignore_signals();
	if (!ft_pwait(v, pid, __WHANG))
		return (__FALSE);
	if (!set_readline_signals(v))
		return (__FALSE);
	if (pipe(v->p1) == -1)
		return (ft_leave(v, EXIT_FAILURE, "pipe", __PERROR));
	return (ft_heredoc2(v));
}

t_bool	ft_heredoc2(t_vars *v)
{
	int	pid;

	pid = 0;
	pid = fork();
	if (pid == -1)
		return (ft_leave(v, EXIT_FAILURE, "fork", __PERROR));
	if (pid == 0)
		ft_heredoc_op2(v);
	if (!ft_fclose(v, &v->outfd) || !ft_fclose(v, &v->p1[1]) || \
		!ft_fclose(v, &v->hdoc_fd))
		return (__FALSE);
	v->hdoc_fd = dup(v->p1[0]);
	if (!ft_fclose(v, &v->p1[0]))
		return (__FALSE);
	if (v->hdoc_fd < 0)
		return (ft_leave(v, EXIT_FAILURE, "dup", __PERROR));
	if (!ft_pwait(v, pid, WNOHANG))
		return (__FALSE);
	return (__TRUE);
}

void	ft_heredoc_op1(t_vars *v)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	if (!line)
		ft_signal_terminate(v);
	while (ft_strncmp(line, v->limiter, ft_strlen(v->limiter) + 1))
	{
		if (v->flg_expand_in_hdoc)
		{
			line = expand_words_of_line(v, line);
			if (!line)
				ft_exitbackprocss(v, v->exitstatus);
		}
		ft_putendl_fd(line, v->outfd);
		ft_freestr(&line);
		line = readline("> ");
		if (!line)
			ft_signal_terminate(v);
	}
	ft_freestr(&line);
	ft_fclose(v, &v->outfd);
	ft_exitbackprocss(v, EXIT_SUCCESS);
	return ;
}

void	ft_heredoc_op2(t_vars *v)
{
	char	*line;

	line = NULL;
	if (!ft_fclose(v, &v->p1[0]) || !ft_fclose(v, &v->infd) || \
		!ft_fclose(v, &v->outfd))
		ft_exitbackprocss(v, v->exitstatus);
	v->infd = open(v->ftemp1, O_RDONLY);
	if (v->infd == -1)
		ft_exitbackprocss(v, !ft_leave(v, EXIT_FAILURE, v->ftemp1, __PERROR));
	line = get_next_line(v->infd);
	while (line)
	{
		if (write(v->p1[1], line, ft_strlen(line)) < 0)
		{
			ft_freestr(&line);
			ft_exitbackprocss(v, EXIT_FAILURE);
		}
		ft_freestr(&line);
		line = get_next_line(v->infd);
	}
	ft_freestr(&line);
	ft_exitbackprocss(v, EXIT_SUCCESS);
	return ;
}

void	ft_signal_terminate(t_vars *v)
{
	if (g_global != SIGINT)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by ", 2);
		ft_putstr_fd("end-of-file (wanted `", 2);
		ft_putstr_fd(v->limiter, 2);
		ft_putstr_fd("')\n", 2);
		ft_exitbackprocss(v, EXIT_SUCCESS);
	}
	else
		ft_exitbackprocss(v, 128 + SIGINT);
}
