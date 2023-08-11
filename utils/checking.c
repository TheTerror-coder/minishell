/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 19:40:47 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/09 15:05:00 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_checkio(t_vars *v)
{
	if (v->flg_infile)
	{
		if (access(v->infile, R_OK))
			perror(v->infile);
	}
	if (v->flg_outfile || v->flg_outappend)
	{
		if (access(v->outfile, W_OK))
			perror(v->outfile);
	}
	return (__TRUE);
}

t_bool	ft_cmdidentity(t_vars *v)
{
	if (v)
		return (__TRUE);
	return (__TRUE);
}
