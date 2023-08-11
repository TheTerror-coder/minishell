/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 19:58:18 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 20:07:55 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft00.h"

char	*ft_strnstr(const char *s1, const char *s2, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!s2[i])
		return ((char *) s1);
	while (i < len && s1[i] != 0)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s2[j] != 0 && i < len && (s1[i] == s2[j]))
			{
				i++;
				j++;
			}
			if (s2[j] == '\0')
				return ((char *) &s1[i - j]);
			i -= (j - 1);
		}
		else
			i++;
	}
	return (0);
}
