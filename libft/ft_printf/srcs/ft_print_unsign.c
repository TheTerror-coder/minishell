/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsign.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 20:01:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:18 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

int	ft_unsign_op(unsigned int n, int printed_len)
{
	unsigned int	div;
	unsigned int	mod;

	div = n / 10;
	mod = n % 10;
	printed_len++;
	if (div != 0)
		printed_len = ft_unsign_op(div, printed_len);
	ft_putnbr_fd(mod, 1);
	return (printed_len);
}

t_bool	ft_print_unsign(t_vars *v, unsigned int n)
{
	v->len += ft_unsign_op(n, 0);
	return (__TRUE);
}

t_bool	ft_op_unsign(t_vars *v, unsigned int n)
{
	t_bool	fdbk;
	int		len;

	if (v->_dot)
		len = v->precision - ft_nbrlen((long long int) n);
	else
		len = v->width - ft_nbrlen((long long int) n);
	fdbk = __TRUE;
	if (len > 0)
		fdbk = ft_print_first(v, len);
	if (fdbk)
		fdbk = ft_print_unsign(v, n);
	if (fdbk && len > 0)
		fdbk = ft_print_last(v, len);
	return (fdbk);
}
