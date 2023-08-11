/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setpipeline.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 21:13:22 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/03 21:41:51 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_setlst(t_vars *v, int x, int i);

t_bool	ft_setpipeline(t_vars *v)
{
	int	i;
	int	x;

	v->jx = 0;
	i = 0;
	x = 0;
	while (v->argv[i])
	{
		while (v->argv[i] && ft_strncmp(v->argv[i], "|", ft_strlen(v->argv[i]) + 1))
			i++;
		if (!ft_setlst(v, x, i))
			return (__FALSE);
		if (v->argv[i])
			i++;
		x = i;
		v->jx++;
	}

// int d = 0;
// 	while (d < v->nb)
// 	{
// i = 0;
// while (v->lst[d][i])
// {
// 	ft_putendl_fd(v->lst[d][i], 2);
// 	i++;
// }
// 		d++;
// 	}
// ft_exitprocss(v, EXIT_SUCCESS);
	return (__TRUE);
}

t_bool	ft_setlst(t_vars *v, int x, int i)
{
	int	k;

	k = 0;
	if (v->jx >= v->nb)
		return (ft_goprompt("list index error", PRINT_ERROR));
	v->lst[v->jx] = ft_calloc((i - x) + 1, sizeof(char *));
	if (!v->lst[v->jx])
		return (ft_goprompt(__FALLOC, PRINT_ERROR));
	while (x < i && v->argv[x])
	{
		v->lst[v->jx][k] = ft_strdup(v->argv[x]);
		if (!v->lst[v->jx][k])
			return (ft_goprompt(__FALLOC, PRINT_ERROR));
		k++;
		x++;
	}
	return (__TRUE);
}