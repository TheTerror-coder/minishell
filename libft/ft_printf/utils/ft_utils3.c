/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:29:44 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 01:59:40 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

void	ft_checkprecision(t_vars *v)
{
	int	i;

	i = v->i;
	if (v->fmt[i + 1] == '.')
	{
		i++;
		v->_dot = _TRUE_;
		if (ft_isdigit(v->fmt[i + 1]))
		{
			v->precision = ft_atoi(&v->fmt[i + 1]);
			i += ft_nbrlen((long long int) v->precision);
		}
		else
			v->precision = 0;
	}
	v->i = i;
}

void	ft_checkflags(t_vars *v)
{
	int	i;

	i = v->i;
	while (ft_isflag(v->fmt[i + 1]))
	{
		v->_noflag = _FALSE_;
		if (v->fmt[i + 1] == '-')
			v->_minus = _TRUE_;
		else if (v->fmt[i + 1] == '0')
			v->_zero = _TRUE_;
		else if (v->fmt[i + 1] == '#')
			v->_sharp = _TRUE_;
		else if (v->fmt[i + 1] == ' ')
			v->_space = _TRUE_;
		else if (v->fmt[i + 1] == '+')
			v->_plus = _TRUE_;
		i++;
	}
	v->i = i;
}

void	ft_checkwidth(t_vars *v)
{
	int	i;

	i = v->i;
	if (ft_iswidth(v->fmt[i + 1]))
	{
		v->width = ft_atoi(&v->fmt[i + 1]);
		i += ft_nbrlen((long long int) v->width);
	}
	v->i = i;
}

t_bool__	ft_checkoptionals(t_vars *v)
{
	ft_checkflags(v);
	ft_checkwidth(v);
	ft_checkprecision(v);
	return (_TRUE_);
}
