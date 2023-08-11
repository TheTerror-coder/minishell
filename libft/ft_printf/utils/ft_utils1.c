/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 18:01:48 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:30 by TheTerror        ###   ########lyon.fr   */
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
	var->_noflag = __TRUE;
	var->_minus = __FALSE;
	var->_zero = __FALSE;
	var->_dot = __FALSE;
	var->_sharp = __FALSE;
	var->_space = __FALSE;
	var->_plus = __FALSE;
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
