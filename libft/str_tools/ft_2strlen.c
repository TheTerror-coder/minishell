/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2strlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 21:26:06 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 21:31:46 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

unsigned int	ft_2strlen(char **sstr)
{
	int	i;

	i = 0;
	if (!sstr)
		return (0);
	while (sstr[i])
		i++;
	return (i);
}
