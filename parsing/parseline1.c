/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:49:16 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/03 14:15:33 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_parseline(t_vars *v, int i);
t_bool	ft_pipecase(t_vars *v);
t_bool	ft_spacecase(t_vars *v, int *i, int x);
t_bool	ft_quotecase(t_vars *v, int *i, int x);
t_bool	ft_delc(t_vars *v, char c);
void	ft_appendnull(t_vars *v);

t_bool	ft_setargv(t_vars *v)
{
	v->jx = 0;
	ft_free2str(&v->argv);
	v->argv = ft_splitwset(v->line, " \t");
	if (!v->argv || !v->argv[0])
		return (ft_goprompt(NULL, PRINT_ERROR));
	if (ft_strchr(v->line, '|'))
		ft_pipecase(v);
	if (!ft_parseline(v, 0))
		return (__FALSE);
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

t_bool	ft_parseline(t_vars *v, int i)
{
	int	x;

	x = 0;
	while (v->line[i])
	{
		while (v->line[i] == ' ' || v->line[i] == '\t')
		{
			i++;
			x = i;
		}
		while (v->line[i] && !ft_isseperator(v->line[i], &v->line[i + 1]))
			i++;
// ft_putendl_fd(&v->line[i], 1);
		if (v->line[i] == ' ' || v->line[i] == '\t' || (!v->line[i] && i - x))
		{
			if (!ft_spacecase(v, &i, x))
				return (__FALSE);
		}
		else if (v->line[i])
		{
			if (!ft_quotecase(v, &i, x))
				return (__FALSE);
			i++;
		}
// ft_putnbr_fd(i, 1);
// ft_putendl_fd("hello", 1);
	}
	ft_appendnull(v);
	return (__TRUE);
}

void	ft_appendnull(t_vars *v)
{
	if (v->jx)
	{
		while (v->argv[v->jx])
		{
			free(v->argv[v->jx]);
			v->argv[v->jx] = NULL;
			v->jx++;
		}
	}
}
		