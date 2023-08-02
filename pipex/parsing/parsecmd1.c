/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:49:16 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:02:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_parsecmd(t_vars *v, int i);
t_bool	ft_spacecase__2(t_vars *v, int *i, int x);
t_bool	ft_quotecase__2(t_vars *v, int *i, int x);
t_bool	ft_delc__2(t_vars *v, char c);
void	ft_appendnull__2(t_vars *v);
t_bool	ft_isseperator__2(char c, char *suite);

t_bool	ft_setcmd(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	var->jx = 0;
	ft_free2str(&var->cmdlst[var->lcmd]);
	var->cmdlst[var->lcmd] = ft_splitwset(var->argv[var->d], " \t");
	if (!var->cmdlst[var->lcmd] || !var->cmdlst[var->lcmd][0])
		return (__FALSE);
	if (!ft_parsecmd(v, 0))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_parsecmd(t_vars *v, int i)
{
	t_ppex	*var;
	int		x;

	var = v->var;
	x = 0;
	while (var->argv[var->d][i])
	{
		while (var->argv[var->d][i] == ' ' || var->argv[var->d][i] == '\t')
		{
			i++;
			x = i;
		}
		while (var->argv[var->d][i] && !ft_isseperator__2(var->argv[var->d][i], &var->argv[var->d][i + 1]))
			i++;
// ft_putendl_fd(&v->var->argv[v->var->d][i], 1);
		if (var->argv[var->d][i] == ' ' || var->argv[var->d][i] == '\t' || (!var->argv[var->d][i] && i - x))
		{
			if (!ft_spacecase__2(v, &i, x))
				return (__FALSE);
		}
		else if (var->argv[var->d][i])
		{
			if (!ft_quotecase__2(v, &i, x))
				return (__FALSE);
			i++;
		}
// ft_putnbr_fd(i, 1);
// ft_putendl_fd("hello", 1);
	}
	ft_appendnull__2(v);
	return (__TRUE);
}

void	ft_appendnull__2(t_vars *v)
{
	t_ppex	*var;

	var = v->var;
	if (var->jx)
	{
		while (var->cmdlst[var->lcmd][var->jx])
		{
			free(var->cmdlst[var->lcmd][var->jx]);
			var->cmdlst[var->lcmd][var->jx] = NULL;
			var->jx++;
		}
	}
}

t_bool	ft_isseperator__2(char c, char *suite)
{
	if (c == ' ' || c == '\t')
		return (__TRUE);
	if (c == "'"[0])
	{
		if (ft_strchr(suite, "'"[0]))
			return (__TRUE);
		return (__FALSE);
	}
	if (c == '"') 
	{
		if (ft_strchr(suite, '"'))
			return (__TRUE);
		return (__FALSE);
	}
	return (__FALSE);
}
