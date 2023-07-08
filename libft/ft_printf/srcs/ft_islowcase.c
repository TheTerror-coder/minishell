/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islowcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:51:12 by TheTerror         #+#    #+#             */
/*   Updated: 2023/03/31 15:16:06 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_srcs.h"

int	ft_islowcase(int c)
{
	unsigned char	cc;

	cc = c;
	if (cc >= 'a' && cc <= 'z')
		return (1);
	return (0);
}
