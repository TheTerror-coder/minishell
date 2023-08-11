/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:58:16 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:15 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

t_bool	ft_print_int(t_vars *v, int n)
{
	t_bool			fdbk;
	unsigned int	nb;

	nb = n;
	fdbk = __TRUE;
	if (n < 0)
		nb = n * -1;
	if (n < 0 && !v->_dot && !v->_zero)
		ft_print_char(v, '-');
	fdbk = ft_print_unsign(v, nb);
	return (fdbk);
}

t_bool	ft_handle_exc1(t_vars *v, int n)
{
	int		len;
	t_bool	fdbk;

	fdbk = __TRUE;
	if (v->width && v->_dot)
	{
		len = ft_nbrlen((long long int) n);
		if (len < v->precision)
		{
			len = v->precision;
			if (n < 0)
				len++;
		}
		if (v->_space || v->_plus)
			len++;
		len = v->width - len;
		if (len > 0)
			fdbk = ft_put_spaces(v, len);
	}
	return (fdbk);
}

t_bool	ft_handle_exc2(t_vars *v, int n)
{
	t_bool	fdbk;

	fdbk = __TRUE;
	if (n >= 0 && v->_space)
		fdbk = ft_print_char(v, ' ');
	if (n >= 0 && v->_plus)
		fdbk = ft_print_char(v, '+');
	if (n < 0 && (v->_dot || v->_zero))
		fdbk = ft_print_char(v, '-');
	return (fdbk);
}

t_bool	ft_op_int(t_vars *v, int n)
{
	t_bool			fdbk;
	int				len;

	fdbk = __TRUE;
	if (v->_dot)
		len = v->precision - ft_nbrlen((long long int) n);
	else
		len = v->width - ft_nbrlen((long long int) n);
	fdbk = ft_handle_exc1(v, n);
	if (n < 0 && v->_dot)
		len++;
	if (n <= 0 && !v->_dot && (v->_space || v->_plus))
		len--;
	fdbk = ft_handle_exc2(v, n);
	if (len > 0)
		fdbk = ft_print_first(v, len);
	if (fdbk)
		fdbk = ft_print_int(v, n);
	if (fdbk && len > 0)
		fdbk = ft_print_last(v, len);
	return (fdbk);
}
