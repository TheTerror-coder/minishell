/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sw_optionals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:43:28 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 01:59:40 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_bonus.h"

t_bool__	ft_print_first(t_vars *v, int len)
{
	t_bool__	fdbk;

	fdbk = _TRUE_;
	if (v->_dot)
		fdbk = ft_put_zeros(v, len);
	else if (v->_zero && !v->_minus)
		fdbk = ft_put_zeros(v, len);
	else if (v->width && !v->_minus && !v->_dot)
		fdbk = ft_put_spaces(v, len);
	return (fdbk);
}

t_bool__	ft_print_last(t_vars *v, int len)
{
	t_bool__	fdbk;

	fdbk = _TRUE_;
	if (v->_minus)
		fdbk = ft_put_spaces(v, len);
	return (fdbk);
}
