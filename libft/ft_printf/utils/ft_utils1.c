/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:01:48 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 01:58:03 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int	ft_hexlen(unsigned long long int nbr)
{
	unsigned long long int	div;
	int						len;

	len = 1;
	div = nbr / 16;
	while (div)
	{
		div /= 16;
		len++;
	}
	return (len);
}

int	ft_nbrlen(long long int nbr)
{
	long long int	div;
	int				len;

	len = 1;
	if (nbr < 0)
	{
		len++;
		nbr *= -1;
	}
	div = nbr / 10;
	while (div)
	{
		div /= 10;
		len++;
	}
	return (len);
}

void	ft_free_var(t_vars *var)
{
	if (var)
		free(var);
}

void	ft_raz_flags(t_vars *var)
{
	var->width = 0;
	var->precision = 0;
	var->_noflag = _TRUE_;
	var->_minus = _FALSE_;
	var->_zero = _FALSE_;
	var->_dot = _FALSE_;
	var->_sharp = _FALSE_;
	var->_space = _FALSE_;
	var->_plus = _FALSE_;
}

t_vars	*ft_init_var(const char *format)
{
	t_vars	*var;

	var = NULL;
	var = ft_calloc(1, sizeof(t_vars));
	if (!var)
		return (NULL);
	var->i = 0;
	var->len = 0;
	var->fmt = NULL;
	var->fmt = format;
	ft_raz_flags(var);
	return (var);
}
