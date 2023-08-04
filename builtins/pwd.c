/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 03:58:35 by lmohin            #+#    #+#             */
/*   Updated: 2023/08/04 09:31:07 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_pwd(void)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (pwd)
		ft_printf("%s\n", pwd);
	else
		perror("minishell: ft_pwd:");
	free(pwd);
	return (1);
}
