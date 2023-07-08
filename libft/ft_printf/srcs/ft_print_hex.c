/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:34:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:02:57 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

int	ft_hex_op(unsigned int n, char *base, int printed_len)
{
	int				mod;
	unsigned int	div;

	div = n / 16;
	mod = n % 16;
	printed_len++;
	if (div != 0)
		printed_len = ft_hex_op(div, base, printed_len);
	ft_putchar_fd(base[mod], 1);
	return (printed_len);
}

t_bool__	ft_print_hex(t_vars *v, unsigned int n, char up_low)
{
	char	*base;

	base = NULL;
	base = ft_hexa_base(up_low);
	if (!base)
		return (_FALSE_);
	v->len += ft_hex_op(n, base, 0);
	free(base);
	return (_TRUE_);
}

t_bool__	ft_sharpcase(t_vars *v, char up_low)
{
	if (v->_sharp)
	{
		if (ft_isupcase(up_low))
			ft_putstr_fd("0X", 1);
		else if (ft_islowcase(up_low))
			ft_putstr_fd("0x", 1);
		v->len += 2;
	}
	return (_TRUE_);
}

t_bool__	ft_op_hex(t_vars *v, unsigned int n, char up_low)
{
	t_bool__	fdbk;
	int			len;

	fdbk = _TRUE_;
	if (v->_dot)
		len = v->precision - ft_hexlen((unsigned long long int) n);
	else
		len = v->width - ft_hexlen((unsigned long long int) n);
	if (n)
		fdbk = ft_sharpcase(v, up_low);
	if (fdbk && len > 0)
		fdbk = ft_print_first(v, len);
	if (fdbk)
		fdbk = ft_print_hex(v, n, up_low);
	if (fdbk && len > 0)
		fdbk = ft_print_last(v, len);
	return (fdbk);
}
