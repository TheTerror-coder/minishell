/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:22:39 by TheTerror         #+#    #+#             */
/*   Updated: 2023/06/02 18:35:33 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bonus.h"

t_bool	ft_heredoc_op(t_vars *var);
t_bool	ft_ioset_op(t_vars *var, int *infd, int *outfd);

t_bool	ft_heredoc(t_vars *var)
{
	int	pid;

	pid = 0;
	var->exit = EXIT_SUCCESS;
	var->infile_fd = -111;
	if (pipe(var->sp) == -1)
		return (ft_perror(var, EXIT_FAILURE, "pipe", __PERROR));
	if (!ft_ioset_op(var, &var->infile_fd, &var->sp[1]))
		return (__FALSE);
	pid = fork();
	if (pid == -1)
		return (ft_perror(var, EXIT_FAILURE, "fork", __PERROR));
	if (pid == 0)
		if (!ft_heredoc_op(var))
			ft_exitprocss(EXIT_FAILURE, var);
	if (!ft_ioset_op(var, &var->sp[0], &var->p[0][1]))
		return (__FALSE);
	if (!ft_fwait(var, pid, WNOHANG))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_heredoc_op(t_vars *var)
{
	char	*line;

	line = NULL;
	ft_close_tvars(var);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (ft_perror(var, EXIT_FAILURE, \
				"get_next_line() failed", __PRINT));
	while (ft_strncmp(line, var->limiter, ft_strlen(line)))
	{
		if (write(STDOUT_FILENO, line, ft_strlen(line)) == -1)
			return (ft_perror(var, EXIT_FAILURE, "write", __PERROR));
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (ft_perror(var, EXIT_FAILURE, \
					"get_next_line() failed", __PRINT));
	}
	free(line);
	ft_exitprocss(EXIT_SUCCESS, var);
	return (__FALSE);
}
