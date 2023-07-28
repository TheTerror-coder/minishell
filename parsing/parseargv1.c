/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargv1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:36:01 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/24 17:07:00 by TheTerror        ###   ########lyon.fr   */
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
	int		fdbk;

	v->jx = 0;
	while (v->argv[v->jx])
	{
		fdbk = ft_redirections(v);
		if (fdbk == __EXIT_REACHED)
			v->jx++;
		else if (!fdbk)
			return (__FALSE);
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
	ft_freestr(&v->infile);
	v->flg_infile = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->infile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	if (access(v->infile, R_OK))
		return (ft_goprompt(v->infile, __PERROR));
	return (__TRUE);
}

t_bool	ft_setoutfile(t_vars *v)
{
	int	fd;

	ft_freestr(&v->outfile);
	v->flg_outfile = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->outfile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	fd = open(v->outfile, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (fd == -1)
		ft_goprompt(v->outfile, __PERROR);
	ft_fclose(&fd);
	return (__TRUE);
}

t_bool	ft_setheredoc(t_vars *v)
{
	ft_freestr(&v->limiter);
	v->flg_heredoc = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->limiter = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	return (__TRUE);
}

t_bool	ft_setoutappend(t_vars *v)
{
	int	fd;

	ft_freestr(&v->outfile);
	v->flg_outappend = __TRUE;
	if (v->argv[v->jx + 1])
	{
		v->outfile = v->argv[v->jx + 1];
		v->argv[v->jx + 1] = NULL;
	}
	else
		return (v->jx++, ft_goprompt("syntax error near unexpected token `newline'", PRINT_ERROR));
	ft_adjustargv(v, v->jx, v->jx + 2);
	fd = open(v->outfile, O_CREAT | O_WRONLY | O_APPEND, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (fd == -1)
		ft_goprompt(v->outfile, __PERROR);
	ft_fclose(&fd);
	return (__TRUE);
}
