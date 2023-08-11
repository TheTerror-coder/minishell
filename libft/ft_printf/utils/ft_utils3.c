/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:29:44 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:34 by TheTerror        ###   ########lyon.fr   */
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
		v->_dot = __TRUE;
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
		v->_noflag = __FALSE;
		if (v->fmt[i + 1] == '-')
			v->_minus = __TRUE;
		else if (v->fmt[i + 1] == '0')
			v->_zero = __TRUE;
		else if (v->fmt[i + 1] == '#')
			v->_sharp = __TRUE;
		else if (v->fmt[i + 1] == ' ')
			v->_space = __TRUE;
		else if (v->fmt[i + 1] == '+')
			v->_plus = __TRUE;
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

t_bool	ft_checkoptionals(t_vars *v)
{
	ft_checkflags(v);
	ft_checkwidth(v);
	ft_checkprecision(v);
	return (__TRUE);
}
