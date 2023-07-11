/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:49:16 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/11 16:06:37 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_goprompt(char *msg, t_typ action)
{
	if (!msg)
		return (__FALSE);
	if (action == PRINT_ERROR)
		ft_putendl_fd(msg, 1);
	else
		perror(msg);
	return (__FALSE);
}

t_bool	ft_setargv(t_vars *v)
{
	v->argv = ft_split(v->line, ' ');
	if (!v->argv || !v->argv[0])
		return (ft_goprompt(NULL, PRINT_ERROR));
	return (__TRUE);
}
