/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:37:04 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/03 22:51:04 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_pipecase(t_vars *v)
{
	char	**sstr;

	v->flg_pipeline = __TRUE;
	sstr = ft_split(v->line, '|');
	if (!sstr || !sstr[0])
		return (__FALSE);
	v->nb = ft_2strlen(sstr);
	ft_free_lst(v);
	v->lst = ft_calloc(v->nb + 1, sizeof(char **));
	ft_free2str(&sstr);
	if (!v->lst)
		return(ft_goprompt("failed allocation", PRINT_ERROR));
	return (__TRUE);
}

t_bool	ft_spacecase(t_vars *v, int *i, int x)
{
	ft_freestr(&v->str);
// ft_putnbr_fd(*i - x, 1);
// ft_putendl_fd("\n", 1);
	v->str = ft_substr(v->line, x, (*i - x));
	if (!v->str)
		return (__FALSE);
	ft_freestr(&v->argv[v->jx]);
	v->argv[v->jx] = ft_strtrim(v->str, " \t");
	if (!v->argv[v->jx])
		return (__FALSE);
	if (v->argv[v->jx][0])
		v->jx++;
	return (__TRUE);
}
 
t_bool	ft_delc(t_vars *v, char c)
{
	char	**sstr;

	sstr = ft_split(v->argv[v->jx], c);
	if (!sstr)
		return (__FALSE);
	free(v->argv[v->jx]);
	v->argv[v->jx] = ft_strjoin(sstr[0], sstr[1]);
	ft_free2str(&sstr);
	if (!v->argv[v->jx])
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_quotecase(t_vars *v, int *i, int x)
{
	char	c;

	c = v->line[*i];
	ft_freestr(&v->str);
	ft_skip_partquoted(v->line, i);
// ft_putnbr_fd(*i - x, 1);
// ft_putendl_fd("\n", 1);
// ft_putendl_fd("\n", 1);
	v->str = ft_substr(v->line, x, (*i - x));
	if (!v->str)
		return (__FALSE);
	ft_freestr(&v->argv[v->jx]);
	v->argv[v->jx] = ft_strtrim(v->str, ft_setofquote(v, c));
	if (!v->argv[v->jx])
		return (__FALSE);
	if (ft_strchr(v->argv[v->jx], c))
		if (!ft_delc(v, c))
			return (__FALSE);
	v->jx++;
	return (__TRUE);
}
