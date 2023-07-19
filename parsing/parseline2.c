/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:37:04 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/16 14:38:48 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_pipecase(t_vars *v)
{
	int	i;

	i = 0;
	if (v->str)
		free(v->str);
	v->str = NULL;
	ft_freesplit(v->argv);
	v->argv = ft_split(v->line, '|');
	if (!v->argv || !v->argv[0])
		ft_exitprocss(v, EXIT_FAILURE);
	while (v->argv[i])
	{
		v->str = ft_strtrim(v->argv[i], " ");
		if (!v->str)
			ft_exitprocss(v, EXIT_FAILURE);
		free(v->argv[i]);
		v->argv[i] = v->str;
		v->str = NULL;
		i++;
	}
	return (__TRUE);
}

t_bool	ft_spacecase(t_vars *v, int *i, int x)
{
	if (v->str)
		free(v->str);
	v->str = NULL;
	v->str = ft_substr(v->line, x, (*i - x));
	if (!v->str)
		ft_exitprocss(v, EXIT_FAILURE);
	if (v->argv[v->jx])
		free(v->argv[v->jx]);
	v->argv[v->jx] = NULL;
	v->argv[v->jx] = ft_strtrim(v->str, " ");
	if (!v->argv[v->jx])
		ft_exitprocss(v, EXIT_FAILURE);
	if (v->argv[v->jx][0])
		v->jx++;
	return (__TRUE);
}

t_bool	ft_delc(t_vars *v, char c)
{
	char	**sstr;

	sstr = ft_split(v->argv[v->jx], c);
	if (!sstr)
		ft_exitprocss(v, EXIT_FAILURE);
	free(v->argv[v->jx]);
	v->argv[v->jx] = ft_strjoin(sstr[0], sstr[1]);
	ft_freesplit(sstr);
	sstr = NULL;
	if (!v->argv[v->jx])
		ft_exitprocss(v, EXIT_FAILURE);
	return (__TRUE);
}

t_bool	ft_quotecase(t_vars *v, int *i, int x)
{
	char	c;

	c = v->line[*i];
	if (v->str)
		free(v->str);
	v->str = NULL;
	ft_skip_partquoted(v->line, i);
	v->str = ft_substr(v->line, x, (*i - x));
	if (!v->str)
		ft_exitprocss(v, EXIT_FAILURE);
	if (v->argv[v->jx])
		free(v->argv[v->jx]);
	v->argv[v->jx] = NULL;
	v->argv[v->jx] = ft_strtrim(v->str, ft_setofquote(v, c));
	if (!v->argv[v->jx])
		ft_exitprocss(v, EXIT_FAILURE);
	if (ft_strchr(v->argv[v->jx], c))
		ft_delc(v, c);
	v->jx++;
	return (__TRUE);
}
