/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iosetter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:13:51 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/10 17:06:48 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_io_firstcmnd(t_vars *v);
int	ft_io_lastcmnd(t_vars *v);

int	ft_ioset(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (var->i == 0)
		return (ft_io_firstcmnd(v));
	else if (var->i < (var->nbcmd - 1))
		return (ft_ioset_op(&var->ff, &var->p[var->i][1]));
	else
		return (ft_io_lastcmnd(v));
	return (__TRUE);
}

int	ft_io_firstcmnd(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (v->flg_infile)
	{
		if (access(v->infile, R_OK))
		{
			perror(v->infile);
			if (!ft_fclose(&var->p[0][1]))
				return (__FALSE);
			return (__SKIP);
		}
		return (ft_inredir(v, &var->p[0][1]));
	}
	if (v->flg_heredoc)
		return (ft_heredocredir(v, &var->p[0][1]));
	if (var->infile_fd < 0)
		return (ft_perror(EXIT_FAILURE, "infile_fd error", __PRINT));
	if (!ft_ioset_op(&var->infile_fd, &var->p[0][1]))
		return (__FALSE);
	return (__TRUE);
}

int	ft_io_lastcmnd(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
// ft_putendl_fd("hehhhe", 2);
// ft_putendl_fd(var->cmdlst[var->i][0], 2);
	if (v->flg_outfile)
		return (ft_outredir(v, &var->ff));
	if (v->flg_outappend)
		return (ft_outappendredir(v, &var->ff));
	if (var->outfile_fd < 0)
		return (ft_perror(EXIT_FAILURE, "outfile_fd error", __PERROR));
	if (!ft_ioset_op(&var->ff, &var->outfile_fd))
		return (__FALSE);
	return (__TRUE);
}
