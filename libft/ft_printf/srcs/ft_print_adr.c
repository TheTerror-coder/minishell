/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:17:56 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:03:33 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

t_bool__	ft_adr_op(t_vars *v, unsigned long long int n)
{
	unsigned long long int		div;
	unsigned int				mod;
	t_bool__					fdbk;

	fdbk = _TRUE_;
	div = n / 16;
	mod = n % 16;
	if (div != 0)
		fdbk = ft_adr_op(v, div);
	if (fdbk)
		fdbk = ft_print_hex(v, mod, 'm');
	return (fdbk);
}

t_bool__	ft_print_adr(t_vars *v, unsigned long long int n)
{
	t_bool__	fdbk;

	fdbk = _TRUE_;
	if (!n)
	{
		ft_putstr_fd("(nil)", 1);
		v->len += 5;
		return (_TRUE_);
	}
	if (!v->_dot)
	{
		ft_putstr_fd("0x", 1);
		v->len += 2;
	}
	fdbk = ft_adr_op(v, n);
	return (fdbk);
}

t_bool__	ft_op_adr(t_vars *v, unsigned long long int n)
{
	t_bool__	fdbk;
	int			len;

	if (v->_dot)
		len = v->precision - ft_hexlen(n);
	else
		len = v->width - ft_hexlen(n) - 2;
	fdbk = _TRUE_;
	if (!n)
		len -= 2;
	if (n && v->_dot)
	{
		ft_putstr_fd("0x", 1);
		v->len += 2;
	}
	if (len > 0)
		fdbk = ft_print_first(v, len);
	if (fdbk)
		fdbk = ft_print_adr(v, n);
	if (fdbk && len > 0)
		fdbk = ft_print_last(v, len);
	return (fdbk);
}
