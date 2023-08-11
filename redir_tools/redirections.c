/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:52:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/10 17:01:21 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_setinfile(t_vars *v);
t_bool	ft_setoutfile(t_vars *v);
t_bool	ft_setheredoc(t_vars *v);
t_bool	ft_setoutappend(t_vars *v);

t_bool	ft_redirections(t_vars *v)
{
	if (!ft_strncmp(v->argv[v->jx], "<", ft_strlen(v->argv[v->jx]) + 1))
		return (ft_setinfile(v));
	if (!ft_strncmp(v->argv[v->jx], ">", ft_strlen(v->argv[v->jx]) + 1))
		return (ft_setoutfile(v));
	if (!ft_strncmp(v->argv[v->jx], "<<", ft_strlen(v->argv[v->jx]) + 2))
		return (ft_setheredoc(v));
	if (!ft_strncmp(v->argv[v->jx], ">>", ft_strlen(v->argv[v->jx]) + 2))
		return (ft_setoutappend(v));
	return (__EXIT_REACHED);
}

t_bool	ft_setinfile(t_vars *v)
{
	ft_freestr(&v->infile);
	v->flg_infile = __TRUE;
	v->flg_heredoc = __FALSE;
	if (v->argv[v->jx + 1])
	{
		v->infile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt(__SERROR, PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}

t_bool	ft_setoutfile(t_vars *v)
{
	ft_freestr(&v->outfile);
	v->flg_outfile = __TRUE;
	v->flg_outappend = __FALSE;
	if (v->argv[v->jx + 1])
	{
		v->outfile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt(__SERROR, PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}

t_bool	ft_setheredoc(t_vars *v)
{
	ft_freestr(&v->limiter);
	v->flg_heredoc = __TRUE;
	v->flg_infile = __FALSE;
	if (v->argv[v->jx + 1])
	{
		v->limiter = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt(__SERROR, PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	if (!ft_heredoc(v))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_setoutappend(t_vars *v)
{
	ft_freestr(&v->outfile);
	v->flg_outappend = __TRUE;
	v->flg_outfile = __FALSE;
	if (v->argv[v->jx + 1])
	{
		v->outfile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt(__SERROR, PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}
