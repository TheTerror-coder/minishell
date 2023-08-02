/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:19:27 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/01 14:17:05 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool ft_cd(char *path, t_vars *v)
{
	char	*new_pwd;

	if (chdir(path) == -1)
	{
		perror("ft_cd->chdir");
		return (1);
	}
	ft_set_pwd(v);
	new_pwd = ft_strjoin("PWD=", v->pwd);
	if (!new_pwd)
		return (1);
	ft_export(v, new_pwd);
	return (0);
}
