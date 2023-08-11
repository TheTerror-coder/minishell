/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:04:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 20:07:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft00.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*p;
	unsigned int	i;

	i = 0;
	p = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			p = &s[i];
		i++;
	}
	if (s[i] == (unsigned char) c)
		p = &s[i];
	return ((char *) p);
}
