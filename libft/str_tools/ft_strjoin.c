/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:11:45 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/30 08:25:58 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*str;

	if (!s1)
		return (ft_strdup(s2));
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	len1 = 0;
	len2 = 0;
	while (s1[len1])
	{
		str[len1] = s1[len1];
		len1++;
	}
	while (s2[len2])
	{
		str[len1] = s2[len2];
		len1++;
		len2++;
	}
	str[len1] = 0;
	return (str);
}
