/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioredir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:54:11 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/13 18:08:27 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_inredir(t_vars *v, char *infile)
{
// ft_putendl_fd("-----inredir------", 2);
	int	nada;

	nada = __CLOSED_FD;
	if (!ft_fclose(&v->infd))
		return (__FALSE);
	v->infd = open(infile, O_RDONLY);
	if (v->infd < 0)
		return (ft_goprompt(infile, __PERROR));
	if (!ft_ioset_op(&v->infd, &nada))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_launch_heredoc(t_vars *v, char *limiter)
{
// ft_putendl_fd("-----launch heredoc------", 2);
	ft_freestr(&v->limiter);
	v->limiter = ft_strdup(limiter);
	if (!v->limiter)
		return (ft_goprompt("ft_heredocredir(): ft_strdup() failed", __PRINT));
	if (!ft_heredoc(v))
		return (__FALSE);
	if (v->hdoc_fd < 0)
		return (ft_goprompt("heredoc file descriptor error", __PRINT));
	return (__TRUE);
}

t_bool	ft_heredocredir(t_vars *v)
{
// ft_putendl_fd("-----heredocredir------", 2);
	int	hdoc_fd_dup;
	int	nada;

	nada = __CLOSED_FD;
	hdoc_fd_dup = __CLOSED_FD;
	hdoc_fd_dup = dup(v->hdoc_fd);
	if (hdoc_fd_dup < 0)
		return (ft_goprompt("ft_heredocredir(): dup() failed", __PRINT));
	if (!ft_ioset_op(&hdoc_fd_dup, &nada))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_outredir(t_vars *v, char *outfile)
{
// ft_putendl_fd("-----outredir------", 2);
	int	nada;

	nada = __CLOSED_FD;
	if (!ft_fclose(&v->outfd))
		return (__FALSE);
	v->outfd = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		return (ft_goprompt(outfile, __PERROR));
	if (!ft_ioset_op(&nada, &v->outfd))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_outappendredir(t_vars *v, char *outfile)
{
// ft_putendl_fd("-----outappendredir------", 2);
	int	nada;

	nada = __CLOSED_FD;
	if (!ft_fclose(&v->outfd))
		return (__FALSE);
	v->outfd = open(outfile, O_CREAT | O_WRONLY | O_APPEND, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		return (ft_goprompt(outfile, __PERROR));
	if (!ft_ioset_op(&nada, &v->outfd))
		return ((__FALSE));
	return (__TRUE);
}
