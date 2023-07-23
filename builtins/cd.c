/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 05:19:27 by lmohin            #+#    #+#             */
/*   Updated: 2023/07/23 04:49:39 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool ending_with_slash(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] == '/')
		return (1);
	return (0);
}

t_bool ft_cd(char *path, t_vars *v)
{
	int	i;
	char	*s1;
	char	*s2;

	i = 0;
	while (strncmp((v->envp)[i], "PWD=", 4))
		i++;
	chdir(path);
	if (path[0] != '/' && strncmp(path, "../", 3) && strncmp(path, "..", 3) && strncmp(path, ".", 2) && strncmp(path, "./", 2))
	{
		s1 = ft_strjoin((v->envp)[i], "/");
		s2 = ft_strjoin(s1, path);
		if (ending_with_slash(path))
			ft_strlcpy((v->envp)[i], s2, ft_strlen(s2));
		else
			ft_strlcpy((v->envp)[i], s2, ft_strlen(s2) + 1);
	}
	printf("%s\n", (v->envp)[i]);
	return (0);
}
