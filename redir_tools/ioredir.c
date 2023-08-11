/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioredir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:54:11 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/10 16:48:51 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_inredir(t_vars *v, int *outfd)
{
// if (!v->infile)
// {
// ft_putendl_fd("HHHHHHHHHHHH", 2);

// }
	if (!ft_fclose(&v->infd))
		return (__FALSE);
	v->infd = open(v->infile, O_RDONLY);
	if (v->infd < 0)
		return (ft_goprompt(v->infile, __PERROR));
	if (!ft_ioset_op(&v->infd, outfd))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_heredocredir(t_vars *v, int *outfd)
{
	if (v->hdoc_fd < 0)
		return (ft_goprompt("heredoc file descriptor error", __PRINT));
	if (!ft_ioset_op(&v->hdoc_fd, outfd))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_outredir(t_vars *v, int *infd)
{
	if (!ft_fclose(&v->outfd))
		return (__FALSE);
	v->outfd = open(v->outfile, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		return (ft_goprompt(v->outfile, __PERROR));
	if (!ft_ioset_op(infd, &v->outfd))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_outappendredir(t_vars *v, int *infd)
{
	if (!ft_fclose(&v->outfd))
		return (__FALSE);
	v->outfd = open(v->outfile, O_CREAT | O_WRONLY | O_APPEND, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		return (ft_goprompt(v->outfile, __PERROR));
	if (!ft_ioset_op(infd, &v->outfd))
		return ((__FALSE));
	return (__TRUE);
}
