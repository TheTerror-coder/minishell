/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:29:24 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 20:07:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft00.h"

int	ft_isalpha(int c)
{
	if (c >= 0 && c <= 255)
	{
		if (c >= 'A' && c <= 'Z')
			return (1);
		if (c >= 'a' && c <= 'z')
			return (1);
	}
	return (0);
}