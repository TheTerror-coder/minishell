/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_special_compare.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:46:17 by lmohin            #+#    #+#             */
/*   Updated: 2023/11/02 17:48:19 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	compare_str_and_var(char *env_var, char *str)
{
	if (!ft_strncmp(env_var, str, ft_strlen(str)))
	{
		if (env_var[ft_strlen(str)] != '=' \
			&& env_var[ft_strlen(str)] != '\0')
		{
			return (__FALSE);
		}
		return (__TRUE);
	}
	return (__FALSE);
}
