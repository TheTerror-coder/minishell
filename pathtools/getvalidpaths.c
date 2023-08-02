/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvalidpaths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:02:30 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/30 15:45:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getlinepath(void);
t_bool	ft_rm_path(t_vars *v);

t_bool	ft_setpath2(t_vars *v)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_getlinepath();
	if (!line)
		return (__FALSE);
	v->paths = ft_split(line, ':');
	if (!v->paths)
		return (__FALSE);
	if (!ft_rm_path(v))
		return (__FALSE);
	while (v->paths[i])
	{
		line = v->paths[i];
		v->paths[i] = ft_strjoin(v->paths[i], "/");
		if (!v->paths[i])
		{
			v->paths[i] = line;
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

t_bool	ft_rm_path(t_vars *v)
{
	char	**str;

	str = ft_split(v->paths[0], '=');
	if (!str)
		return (__FALSE);
	free(v->paths[0]);
	v->paths[0] = str[1];
	str[1] = NULL;
	ft_free2str(&str);
	return (__TRUE);
}
