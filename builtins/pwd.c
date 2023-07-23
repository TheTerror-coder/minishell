/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 03:58:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/23 04:12:24 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_pwd(t_vars *v)
{
	int	i;
	char	*s;

	i = 0;
	while ((v->envp)[i] && strncmp((v->envp)[i], "PWD=", 4))
		i++;
	s = ft_substr((v->envp)[i], 4, ft_strlen((v->envp)[i]) - 4);
	if (!s)
		return (0);
	printf("%s\n", s);
	free(s);
	return (1);
}
