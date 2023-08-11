/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 21:36:00 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:16 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

t_bool	ft_print_str(t_vars *v, char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		if (v->_dot && v->precision < 6)
			return (__TRUE);
		ft_putstr_fd("(null)", 1);
		v->len += 6;
		return (__TRUE);
	}
	if (v->_dot)
	{
		while (i < v->precision && str[i])
		{
			ft_print_char(v, str[i]);
			i++;
		}
		return (__TRUE);
	}
	ft_putstr_fd(str, 1);
	v->len += ft_strlen(str);
	return (__TRUE);
}

t_bool	ft_op_str(t_vars *v, char *str)
{
	t_bool	fdbk;
	int		len;

	fdbk = __TRUE;
	len = ft_strlen(str);
	if (v->_dot && v->precision < len)
		len = v->precision;
	len = v->width - len;
	if (!str && (!v->_dot || v->precision >= 6))
		len -= 6;
	if (v->_zero)
		v->_zero = __FALSE;
	if (len > 0 && !v->_dot)
		fdbk = ft_print_first(v, len);
	else if (len > 0 && v->_dot)
	{
		v->_dot = __FALSE;
		fdbk = ft_print_first(v, len);
		v->_dot = __TRUE;
	}
	if (fdbk)
		fdbk = ft_print_str(v, str);
	if (fdbk && len > 0)
		fdbk = ft_print_last(v, len);
	return (fdbk);
}
