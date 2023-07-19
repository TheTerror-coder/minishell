/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:38:57 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/07 15:46:23 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

t_bool	ft_checkargs(t_vars *var)
{
	if (var->argc < 5)
		return (ft_perror(var, EXIT_FAILURE, __MISSARG, __PRINT));
	if (var->argc > 5)
		return (ft_perror(var, EXIT_FAILURE, __MOREARG, __PRINT));
	return (__TRUE);
}

t_bool	ft_heredoc(t_vars *var)
{
	if (1 || var)
		return (__TRUE);
	return (__TRUE);
}
