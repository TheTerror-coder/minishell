/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseline1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:49:16 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/19 19:02:28 by lmohin           ###   ########.fr       */
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
	v->argv = ft_split(v->line, ' ');
	if (!v->argv || !v->argv[0])
		return (ft_goprompt(NULL, PRINT_ERROR));
	if (ft_strchr(v->line, '|'))
	{
		ft_pipecase(v);
		return (__TRUE);
	}
	else
		ft_parseline(v, 0);
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

	x = i;
	while (v->line[i] == ' ')
		i++;
	while (v->line[i])
	{
		if (ft_isseperator(v->line[i], &v->line[i + 1]))
		{
			if (v->line[i] == ' ')
				ft_spacecase(v, &i, x);
			else
				ft_quotecase(v, &i, x);
			x = i + 1;
		}
		i++;
		if (!v->line[i] && i - x)
			ft_spacecase(v, &i, x);
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
