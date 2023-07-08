/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 21:36:00 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:02:21 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

t_bool__	ft_print_str(t_vars *v, char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (v->_dot && v->precision < 6)
			return (_TRUE_);
		ft_putstr_fd("(null)", 1);
		v->len += 6;
		return (_TRUE_);
	}
	if (v->_dot)
	{
		while (i < v->precision && str[i])
		{
			ft_print_char(v, str[i]);
			i++;
		}
		return (_TRUE_);
	}
	ft_putstr_fd(str, 1);
	v->len += ft_strlen(str);
	return (_TRUE_);
}

t_bool__	ft_op_str(t_vars *v, char *str)
{
	t_bool__	fdbk;
	int			len;

	fdbk = _TRUE_;
	len = ft_strlen(str);
	if (v->_dot && v->precision < len)
		len = v->precision;
	len = v->width - len;
	if (!str && (!v->_dot || v->precision >= 6))
		len -= 6;
	if (v->_zero)
		v->_zero = _FALSE_;
	if (len > 0 && !v->_dot)
		fdbk = ft_print_first(v, len);
	else if (len > 0 && v->_dot)
	{
		v->_dot = _FALSE_;
		fdbk = ft_print_first(v, len);
		v->_dot = _TRUE_;
	}
	if (fdbk)
		fdbk = ft_print_str(v, str);
	if (fdbk && len > 0)
		fdbk = ft_print_last(v, len);
	return (fdbk);
}
