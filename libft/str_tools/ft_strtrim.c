/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:43:18 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/09 16:36:12 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_is_in_set(const char *set, char c)
{
	unsigned int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

unsigned int	ft_len(const char *s, char const *set)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = 0;
	while (ft_is_in_set(set, s[i]) != 0)
		i++;
	while (s[i])
	{
		len++;
		i++;
	}
	if (len != 0)
		i--;
	while (ft_is_in_set(set, s[i]) != 0)
	{
		len--;
		i--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	int		k;
	char	*str;

	i = 0;
	len = ft_len(s1, set);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (ft_is_in_set(set, s1[i]) != 0)
		i++;
	while (k < len && s1[i] != 0)
	{
		str[k] = s1[i];
		k++;
		i++;
	}
	str[k] = '\0';
	return (str);
}
