/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 22:37:36 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/30 08:26:41 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned int	ft_count_row(const char *s, char c)
{
	unsigned int	i;
	unsigned int	nbrow;

	i = 0;
	nbrow = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] != 0 && s[i] != c)
				i++;
			nbrow++;
		}
	}
	return (nbrow);
}

unsigned int	ft_count_col(const char *s, char c)
{
	unsigned int	i;

	i = 0;
	while ((s[i] != 0) && (s[i] != c))
		i++;
	return (i);
}

void	ft_free(char **arr, unsigned int ix)
{
	while (ix > 0)
	{
		free(arr[ix]);
		ix--;
	}
	free(arr[ix]);
	free(arr);
}

int	ft_fill(char const *s, char **sstr, char c)
{
	unsigned int	i;
	unsigned int	ix;
	unsigned int	len;

	i = 0;
	ix = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		len = ft_count_col(&s[i], c);
		if (s[i])
		{
			sstr[ix] = ft_substr(s, i, len);
			if (!sstr[ix])
			{
				ft_free(sstr, ix);
				return (0);
			}
			ix++;
		}
		i = len + i;
	}
	sstr[ix] = 0;
	return (55);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	len;
	char			**sstr;

	len = ft_count_row(s, c);
	sstr = malloc(sizeof(char *) * (len + 1));
	if (!sstr)
		return (NULL);
	if (!ft_fill(s, sstr, c))
		return (0);
	return (sstr);
}
