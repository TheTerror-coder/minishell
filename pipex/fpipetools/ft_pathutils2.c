/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathutils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:02:30 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/11 18:31:12 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipetools.h"

char	*ft_getlinepath(void);
t_bool	ft_rm_path(t_vars *var);

t_bool	ft_setpath(t_vars *var)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_getlinepath();
	if (!line)
		return (__FALSE);
	var->paths = ft_split(line, ':');
	if (!var->paths)
		return (__FALSE);
	if (!ft_rm_path(var))
		return (__FALSE);
	while (var->paths[i])
	{
		line = var->paths[i];
		var->paths[i] = ft_strjoin(var->paths[i], "/");
		if (!var->paths[i])
		{
			var->paths[i] = line;
			return (__FALSE);
		}
		free(line);
		i++;
	}
	return (__TRUE);
}

char	*ft_getlinepath(void)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	while (__environ[i])
	{
		line = ft_strnstr(__environ[i], "PATH=", 7);
		if (line)
			return (__environ[i]);
		i++;
	}
	return (NULL);
}

t_bool	ft_rm_path(t_vars *var)
{
	char	**str;

	str = ft_split(var->paths[0], '=');
	if (!str)
		return (__FALSE);
	free(var->paths[0]);
	var->paths[0] = str[1];
	str[1] = NULL;
	ft_freesplit(str);
	return (__TRUE);
}

t_bool	ft_cmdnfnd(t_vars *var)
{
	write (STDERR_FILENO, var->cmdlst[var->i][0], \
			ft_strlen(var->cmdlst[var->i][0]));
	if (!ft_strchr(var->cmdlst[var->i][0], '/'))
		ft_perror(var, var->exit, ": command not found", __PRINT);
	else
		ft_perror(var, var->exit, ": No such file or directory", __PRINT);
	free(var->cmdpath);
	var->cmdpath = NULL;
	return (__SKIP);
}
