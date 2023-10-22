/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvalidpaths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:02:30 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/22 17:07:18 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getlinepath(t_vars *v);
t_bool	ft_rm_path(t_vars *v);
t_bool	ft_add_slash(t_vars *v);

t_bool	ft_set_path_variable(t_vars *v)
{
	char	*line;
	line = ft_getlinepath(v);
	if (!line)
		return (ft_free2str(&v->paths), __TRUE);
	v->paths = ft_split(line, ':');
	if (!v->paths | !v->paths[0])
		return (ft_leave(EXIT_FAILURE, \
			"ft_set_path_variable() : ft_split() failed", __PRINT));
	if (!ft_rm_path(v))
		return (__FALSE);
	if (!ft_add_slash(v))
		return (__FALSE);
	return (__TRUE);
}

char	*ft_getlinepath(t_vars *v)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
	if (!v->envp || !v->envp[0])
		return (ft_leave(EXIT_FAILURE, \
		"minishell: environ fault: envp variable is not set", __PRINT), NULL);
	while (v->envp[i])
	{
		line = ft_strnstr(v->envp[i], "PATH=", 7);
		if (line)
			return (v->envp[i]);
		i++;
	}
	return (NULL);
}

t_bool	ft_rm_path(t_vars *v)
{
	char	**str;

	str = ft_split(v->paths[0], '=');
	if (!str)
		return (ft_leave(EXIT_FAILURE, \
			"ft_rm_path() : ft_split() failed", PRINT_ERROR));
	ft_freestr(&v->paths[0]);
	v->paths[0] = str[1];
	str[1] = NULL;
	ft_free2str(&str);
	return (__TRUE);
}

t_bool	ft_add_slash(t_vars *v)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	while (v->paths[i])
	{
		line = v->paths[i];
		v->paths[i] = ft_strjoin(v->paths[i], "/");
		if (!v->paths[i])
		{
			v->paths[i] = line;
			return (ft_leave(EXIT_FAILURE, \
				"ft_rm_path(): ft_strjoin() failed", __PRINT));
		}
		free(line);
		i++;
	}
	return (__TRUE);
}
