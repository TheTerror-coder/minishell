/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:00:20 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:04 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

char	*ft_hexa_base(char up_low)
{
	char	*base;
	int		i;

	i = 0;
	base = malloc(sizeof(char) * 17);
	if (!base)
		return (NULL);
	if (ft_islowcase(up_low))
	{
		while ("0123456789abcdef"[i])
		{
			base[i] = "0123456789abcdef"[i];
			i++;
		}
	}
	else if (ft_isupcase(up_low))
	{
		while ("0123456789ABCDEF"[i])
		{
			base[i] = "0123456789ABCDEF"[i];
			i++;
		}
	}
	base[i] = 0;
	return (base);
}
