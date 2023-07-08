/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:26:47 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:32 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int	ft_iswidth(char c)
{
	if (c != '0' && ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_isflag(char c)
{
	if (c == '-' || c == '0' || c == '#' || c == ' ' || c == '+')
		return (1);
	return (0);
}

int	ft_is_optional(char c)
{
	if (ft_isflag(c) || ft_iswidth(c) || c == '.')
		return (1);
	return (0);
}

int	ft_isnbr_type(char c)
{
	if (c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X')
		return (1);
	return (0);
}

int	ft_istype(char c)
{
	if (c == 'c' || c == 'd' || c == 'i' || c == 'u' || c == 's')
		return (1);
	else if (c == 'x' || c == 'X' || c == 'p' || c == '%')
		return (1);
	return (0);
}
