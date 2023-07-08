/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:10:13 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 01:59:40 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bonus.h"

t_bool__	ft_put_spaces(t_vars *v, int len)
{
	t_bool__	fdbk;

	fdbk = _TRUE_;
	while (fdbk && len > 0)
	{
		fdbk = ft_print_char(v, ' ');
		len--;
	}
	return (fdbk);
}
