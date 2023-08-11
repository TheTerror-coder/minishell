/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:25:08 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 20:07:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft00.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int		i;
	int					feed;

	i = 0;
	feed = 0;
	if (!s1[i] && !s2[i])
		return (feed);
	while (i < n)
	{
		if (!s1[i] && !s2[i])
			return (feed);
		feed = (unsigned char) s1[i] - (unsigned char) s2[i];
		if (feed != 0)
			return (feed);
		i++;
	}
	return (feed);
}
