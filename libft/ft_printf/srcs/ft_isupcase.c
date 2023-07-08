/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isupcase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:54:15 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:07 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

int	ft_isupcase(int c)
{
	unsigned char	cc;

	cc = c;
	if (cc >= 'A' && cc <= 'Z')
		return (1);
	return (0);
}
