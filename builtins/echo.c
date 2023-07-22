/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 01:22:53 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/22 02:45:46 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_echo(t_vars *v, t_bool n_option)
{
	int	i;

	i = 1;

	while (v->argv[i] != NULL)
	{
		printf("%s", v->argv[i]);
		i++;
		if (v->argv[i] != NULL)
			printf(" ");
	}
	if (!n_option)
		printf("\n");
	return (0);
}