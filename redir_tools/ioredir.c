/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioredir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:54:11 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/27 17:37:40 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* ft_inredir() ensures that 'infile' is openable in read mode then opens it
* as standard input.
*/
t_bool	ft_inredir(t_vars *v, char *infile)
{
	int	nada;
// ft_putendl_fd("ft_inredir()--------", STDERR_FILENO);
	if (!infile)
		return (ft_leave(EXIT_FAILURE, "ambiguous redirect", __PRINT));
	nada = __CLOSED_FD;
	if (!ft_fclose(&v->infd))
		return (__FALSE);
	v->infd = open(infile, O_RDONLY);
	if (v->infd < 0)
		return (ft_leave(EXIT_FAILURE, infile, __PERROR));
	if (!ft_ioset_op(&v->infd, &nada))
		return (__FALSE);
	return (__TRUE);
}

/*
* This function is called to launch ft_heredoc().
* It sets the limiter to be used and wait ft_heredoc to return so
* it can ensure that the file descriptor of the heredocs content is valid
* before exiting.
*/
t_bool	ft_launch_heredoc(t_vars *v, char *limiter)
{
// ft_putendl_fd("ft_launch_heredoc()--------", STDERR_FILENO);
	ft_freestr(&v->limiter);
	v->limiter = ft_strdup(limiter);
	if (!v->limiter)
		return (ft_leave(EXIT_FAILURE, "ft_launch_heredoc(): ft_strdup() failed", __PRINT));
	if (!ft_heredoc(v))
		return (__FALSE);
	if (v->hdoc_fd < 0)
		return (ft_leave(EXIT_FAILURE, "heredoc file descriptor error", __PRINT));
	return (__TRUE);
}

/*
* The heredoc file descriptor is duplicated here because otherwise, when there are
* several heredocs, this function is called as many times to ultimately save the last
* as standard input. So if we close this hdoc_fd, we loose the connection with the 
* here-document content at the first call.
*/
t_bool	ft_heredocredir(t_commands *command)
{
	int	hdoc_fd_dup;
	int	nada;

// ft_putendl_fd("ft_heredocredir()--------", STDERR_FILENO);
	nada = __CLOSED_FD;
	hdoc_fd_dup = __CLOSED_FD;
	hdoc_fd_dup = dup(command->hdoc_fd);
	if (hdoc_fd_dup < 0)
		return (ft_leave(EXIT_FAILURE, "ft_heredocredir(): dup() failed", __PRINT));
	if (!ft_ioset_op(&hdoc_fd_dup, &nada))
		return (__FALSE);
	return (__TRUE);
}

/*
* ft_outredir() ensures that 'outfile' is openable in write mode and then
* opens it as standard output.
*/
t_bool	ft_outredir(t_vars *v, char *outfile)
{
	int	nada;

// ft_putendl_fd("ft_outredir()--------", STDERR_FILENO);
	nada = __CLOSED_FD;
	if (!outfile)
		return (ft_leave(EXIT_FAILURE, "ambiguous redirect", __PRINT));
	if (!ft_fclose(&v->outfd))
		return (__FALSE);
	v->outfd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		return (ft_leave(EXIT_FAILURE, outfile, __PERROR));
	if (!ft_ioset_op(&nada, &v->outfd))
		return (__FALSE);
	return (__TRUE);
}

/*
* ft_outappendredir() ensures that 'outfile' is openable in write mode and then
* opens it as standard output with append mode setted.
*/
t_bool	ft_outappendredir(t_vars *v, char *outfile)
{
	int	nada;

// ft_putendl_fd("ft_outappendredir()--------", STDERR_FILENO);
	nada = __CLOSED_FD;
	if (!outfile)
		return (ft_leave(EXIT_FAILURE, "ambiguous redirect", __PRINT));
	if (!ft_fclose(&v->outfd))
		return (__FALSE);
	v->outfd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		return (ft_leave(EXIT_FAILURE, outfile, __PERROR));
	if (!ft_ioset_op(&nada, &v->outfd))
		return ((__FALSE));
	return (__TRUE);
}
