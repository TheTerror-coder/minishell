/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:07:04 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/06 21:20:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bonus.h"

t_bool	ft_checkargs(t_vars *var)
{
	if (var->argc < 2)
		return (ft_perror(var, EXIT_FAILURE, __AFAULT, __PRINT));
	if (!ft_strncmp(var->argv[1], "here_doc", ft_strlen(var->argv[1])))
	{
		var->heredoc_flg = __TRUE;
		if (var->argc < 6)
			return (ft_perror(var, EXIT_FAILURE, __AFAULT, __PRINT));
		var->limiter = ft_strjoin(var->argv[2], "\n");
		if (!var->limiter)
			return (ft_perror(var, EXIT_FAILURE, NULL, __PRINT));
	}
	else
		if (var->argc < 5)
			return (ft_perror(var, EXIT_FAILURE, __AFAULT, __PRINT));
	return (__TRUE);
}
