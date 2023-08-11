/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:53:24 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/06 16:57:44 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_heredoc_op1(t_vars *v);
t_bool	ft_heredoc_op2(t_vars *v);
t_bool	ft_heredoc2(t_vars *v);

t_bool	ft_heredoc(t_vars *v)
{
	int	pid;

	pid = -1;
	v->exit_code = EXIT_SUCCESS;
	ft_openatemp(v);
	pid = fork();
	if (pid < 0)
		return (ft_goprompt("fork", PRINT_ERROR));
	if (pid == 0)
		if (!ft_heredoc_op1(v))
			ft_exitprocss(v, EXIT_FAILURE);
	if (!ft_pwait(v, pid, __WHANG))
		return (__FALSE);
	if (pipe(v->p1) == -1)
		return (ft_goprompt("pipe", PRINT_ERROR));
	ft_heredoc2(v);
	return (__TRUE);
}

t_bool	ft_heredoc2(t_vars *v)
{
	int	pid;

	pid = 0;
	v->exit_code = EXIT_SUCCESS;
	pid = fork();
	if (pid == -1)
		return (ft_goprompt("fork", PRINT_ERROR));
	if (pid == 0)
		if (!ft_heredoc_op2(v))
			ft_exitprocss(v, EXIT_FAILURE);
	ft_fclose(&v->outfd);
	ft_fclose(&v->p1[1]);
	ft_fclose(&v->hdoc_fd);
	v->hdoc_fd = dup(v->p1[0]);
	ft_fclose(&v->p1[0]);
	if (v->hdoc_fd < 0)
		return (ft_goprompt("dup", __PERROR));
	if (!ft_pwait(v, pid, WNOHANG))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_heredoc_op1(t_vars *v)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	while (ft_strncmp(line, v->limiter, ft_strlen(line) + ft_strlen(v->limiter)))
	{
		ft_putendl_fd(line, v->outfd);
		ft_freestr(&line);
		line = readline("> ");
	}
	ft_freestr(&line);
	ft_fclose(&v->outfd);
	ft_exitprocss(v, __SUCCEED);
	return (__FALSE);
}

t_bool	ft_heredoc_op2(t_vars *v)
{
	char	*line;

	line = NULL;
	ft_fclose(&v->p1[0]);
	ft_fclose(&v->infd);
	ft_fclose(&v->outfd);
	v->infd = open(v->ftemp1, O_RDONLY);
	if (v->infd == -1)
		ft_exitprocss(v, !ft_goprompt(v->ftemp1, __PERROR));
	line = get_next_line(v->infd);
	while (line)
	{
		ft_putstr_fd(line, v->p1[1]);
		ft_freestr(&line);
		line = get_next_line(v->infd);
	}
	ft_freestr(&line);
	ft_exitprocss(v, EXIT_SUCCESS);
	return (__FALSE);
}
