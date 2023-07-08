/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:35:49 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/12 02:10:45 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "lget_next_line.h"

char	*ft_lloc(int len)
{
	char		*arr;
	int			i;

	i = 0;
	if (!len)
		return (NULL);
	arr = malloc(sizeof(char) * len);
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}

int	ft_size(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	ft_gappend(char *line, char *buf, int end_buf)
{
	int	i;

	i = 0;
	if (!end_buf || !line || !buf)
		return (0);
	while (i < end_buf)
	{
		line[i] = buf[i];
		i++;
	}
	return (i);
}

int	ft_check_endl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}
