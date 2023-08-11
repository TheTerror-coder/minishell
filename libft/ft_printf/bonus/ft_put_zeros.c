/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_zeros.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:57:46 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:15:54 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bonus.h"

t_bool	ft_put_zeros(t_vars *v, int len)
{
	t_bool	fdbk;

	fdbk = __TRUE;
	while (fdbk && len > 0)
	{
		fdbk = ft_print_char(v, '0');
		len--;
	}
	return (fdbk);
}
