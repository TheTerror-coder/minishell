/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 05:39:12 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/19 21:51:19 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	char_is_in_str(char *str, char c)
{
	int	i;

	if (c == '\0')
		return (__TRUE);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (__TRUE);
		i++;
	}
	return (__FALSE);
}

t_bool	ft_env(t_vars *v, t_commands *command)
{
	t_env	*tmp;

	if ((command->arguments)[1])
	{
		ft_putstr_fd("minishell: ft_env: not handling parameters", 1);
		return (__FALSE);
	}
	tmp = v->my_env;
	while (tmp != NULL)
	{
		if (char_is_in_str(tmp->var, '='))
		{
			ft_putstr_fd(tmp->var, 1);
			ft_putchar_fd('\n', 1);
		}
		tmp = tmp->next;
	}
	return (__TRUE);
}
