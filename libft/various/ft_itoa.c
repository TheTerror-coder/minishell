/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 15:47:39 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/09 16:36:12 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_set_len(int n)
{
	int	div;
	int	len;

	len = 1;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	div = n / 10;
	while (div != 0)
	{
		div /= 10;
		len++;
	}
	return (len);
}

void	ft_append(char *str, int n, int len)
{
	int	div;
	int	mod;

	mod = n % 10;
	div = n / 10;
	str[len] = 0;
	while (div != 0 && len > 0)
	{
		len--;
		str[len] = mod + 48;
		mod = div % 10;
		div /= 10;
	}
	if (len > 0)
	{
		len--;
		str[len] = mod + 48;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_set_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (n < 0)
	{
		if (n == -2147483648)
		{
			ft_memcpy(str, "-2147483648", len + 1);
			return (str);
		}
		str[0] = '-';
		n *= -1;
	}
	ft_append(str, n, len);
	return (str);
}
