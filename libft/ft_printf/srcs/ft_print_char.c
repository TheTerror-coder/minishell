/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 19:40:05 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:01:48 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

t_bool__	ft_print_char(t_vars *v, int c)
{
	ft_putchar_fd(c, 1);
	v->len++;
	return (_TRUE_);
}

t_bool__	ft_op_char(t_vars *v, int c)
{
	t_bool__	fdbk;
	int			len;

	len = v->width - 1;
	fdbk = _TRUE_;
	if (len > 0 && !v->_dot)
		fdbk = ft_print_first(v, len);
	if (fdbk)
		fdbk = ft_print_char(v, c);
	if (fdbk && len > 0)
		ft_print_last(v, len);
	return (fdbk);
}
