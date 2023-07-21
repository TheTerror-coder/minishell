/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ioredir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:54:11 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/21 14:57:10 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_inredir(t_vars *v)
{
	int	nada;

	nada = -111;
	v->infd = open(v->infile, O_RDONLY);
	if (v->infd == -1)
		ft_exitprocss(v, !ft_goprompt(v->infile, __PERROR));
	if (!ft_ioset_op(&v->infd, &nada))
		ft_exitprocss(v, !ft_goprompt(NULL, __PERROR));
	return (__TRUE);
}

t_bool	ft_outredir(t_vars *v)
{
	int	nada;

	nada = -111;
	v->outfd = open(v->outfile, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		ft_exitprocss(v, !ft_goprompt(v->outfile, __PERROR));
	if (!ft_ioset_op(&nada, &v->outfd))
		ft_exitprocss(v, !ft_goprompt(NULL, __PERROR));
	return (__TRUE);
}

t_bool	ft_outappendredir(t_vars *v)
{
	int	nada;

	nada = -111;
	v->outfd = open(v->outfile, O_CREAT | O_WRONLY | O_APPEND, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		ft_exitprocss(v, !ft_goprompt(v->outfile, __PERROR));
	if (!ft_ioset_op(&nada, &v->outfd))
		ft_exitprocss(v, !ft_goprompt(NULL, __PERROR));
	return (__TRUE);
}
