/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargv1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:36:01 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/21 20:14:48 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_redirections(t_vars *v);
t_bool	ft_setinfile(t_vars *v);
t_bool	ft_setoutfile(t_vars *v);
t_bool	ft_setheredoc(t_vars *v);
t_bool	ft_setoutappend(t_vars *v);

t_bool	ft_parseargv(t_vars *v)
{
	v->jx = 0;
	while (v->argv[v->jx])
	{
		if (!ft_redirections(v))
			v->jx++;
	}
// int	i;
// i = 0;
// while (v->argv[i])
// {
// 	ft_putendl_fd(v->argv[i], 1);
// 	i++;
// }
// ft_exitprocss(v, EXIT_SUCCESS);
	return (__TRUE);
}

t_bool	ft_redirections(t_vars *v)
{
	if (!ft_strncmp(v->argv[v->jx], "<", ft_strlen(v->argv[v->jx])))
		return (ft_setinfile(v), __TRUE);
	if (!ft_strncmp(v->argv[v->jx], ">", ft_strlen(v->argv[v->jx])))
		return (ft_setoutfile(v), __TRUE);
	if (!ft_strncmp(v->argv[v->jx], "<<", ft_strlen(v->argv[v->jx])))
		return (ft_setheredoc(v), __TRUE);
	if (!ft_strncmp(v->argv[v->jx], ">>", ft_strlen(v->argv[v->jx])))
		return (ft_setoutappend(v), __TRUE);
	return (__FALSE);
}

t_bool	ft_adjustargv(t_vars *v, int a, int b)
{
	free(v->argv[a]);
	v->argv[a] = NULL;
	while (v->argv[b])
	{
		v->argv[a] = v->argv[b];
		v->argv[b] = NULL;
		a++;
		b++;
	}
	return (__TRUE);
}

t_bool	ft_setinfile(t_vars *v)
{
//gestion des erreurs: quand '<' est suivi de rien c-a-d lorsquelle est la derniere chaine sur argv
	v->flg_infile = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->infile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
	{
		ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR);
		ft_exitprocss(v, EXIT_FAILURE);
	}
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}

t_bool	ft_setoutfile(t_vars *v)
{
	v->flg_outfile = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->outfile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
	{
		ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR);
		ft_exitprocss(v, EXIT_FAILURE);
	}
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}

t_bool	ft_setheredoc(t_vars *v)
{
	v->flg_heredoc = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->limiter = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
	{
		ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR);
		ft_exitprocss(v, EXIT_FAILURE);
	}
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}

t_bool	ft_setoutappend(t_vars *v)
{
	v->flg_outappend = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->outfile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
	{
		ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR);
		ft_exitprocss(v, EXIT_FAILURE);
	}
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}
