/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 20:07:04 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/10 15:51:18 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_checkargs(t_vars *v)
{
	if (v->var->nbcmd < 2)
		return (ft_perror(EXIT_FAILURE, __AFAULT, __PRINT));
	return (__TRUE);
}
