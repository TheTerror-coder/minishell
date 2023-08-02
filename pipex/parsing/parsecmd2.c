/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:37:04 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:02:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"


t_bool	ft_spacecase__2(t_vars *v, int *i, int x)
{
	t_ppex	*var;

	var = v->var;
	ft_freestr(&var->str);
// ft_putnbr_fd(*i - x, 1);
// ft_putendl_fd("\n", 1);
	var->str = ft_substr(var->argv[var->d], x, (*i - x));
	if (!var->str)
		return (__FALSE);
	ft_freestr(&var->cmdlst[var->lcmd][var->jx]);
	var->cmdlst[var->lcmd][var->jx] = ft_strtrim(var->str, " \t");
	if (!var->cmdlst[var->lcmd][var->jx])
		return (__FALSE);
	if (var->cmdlst[var->lcmd][var->jx][0])
		var->jx++;
	return (__TRUE);
}

t_bool	ft_delc__2(t_vars *v, char c)
{
	t_ppex	*var;
	char	**sstr;

	var = v->var;
	sstr = ft_split(var->cmdlst[var->lcmd][var->jx], c);
	if (!sstr)
		return (__FALSE);
	free(var->cmdlst[var->lcmd][var->jx]);
	var->cmdlst[var->lcmd][var->jx] = ft_strjoin(sstr[0], sstr[1]);
	ft_free2str(&sstr);
	if (!var->cmdlst[var->lcmd][var->jx])
		return (__FALSE);
	return (__TRUE);
}

void	ft_skip_partquoted__2(char *line, int *i)
{
	char	c;

	c = line[*i];
	*i = *i + 1;
	while (line[*i] != c)
		*i = *i + 1;
}

char	*ft_setofquote__2(t_vars *v, char c)
{
	t_ppex	*var;
	char	*set;

	var = v->var;
	set = ft_calloc(2, sizeof(char));
	if (!set)
		return (NULL);
	set[0] = c;
	set[1] = 0;
	ft_freestr(&var->set);
	var->set = set;
	return (set);
}

t_bool	ft_quotecase__2(t_vars *v, int *i, int x)
{
	t_ppex	*var;
	char	c;

	var = v->var;
	c = var->argv[var->d][*i];
	ft_freestr(&var->str);
	ft_skip_partquoted__2(var->argv[var->d], i);
// ft_putnbr_fd(*i - x, 1);
// ft_putendl_fd("\n", 1);
	var->str = ft_substr(var->argv[var->d], x, (*i - x));
	if (!var->str)
		return (__FALSE);
	ft_freestr(&var->cmdlst[var->lcmd][var->jx]);
	var->cmdlst[var->lcmd][var->jx] = ft_strtrim(var->str, ft_setofquote__2(v, c));
	if (!var->cmdlst[var->lcmd][var->jx])
		return (__FALSE);
	if (ft_strchr(var->cmdlst[var->lcmd][var->jx], c))
		if (!ft_delc__2(v, c))
			return (__FALSE);
	var->jx++;
	return (__TRUE);
}
