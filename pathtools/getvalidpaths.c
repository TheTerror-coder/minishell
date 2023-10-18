/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvalidpaths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:02:30 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/17 23:51:52 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getlinepath(t_vars *v);
t_bool	ft_rm_path(t_vars *v);

t_bool	ft_setpath2(t_vars *v)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_getlinepath(v);
	if (!line)
		return (ft_leave("PATH unfound", PRINT_ERROR));
	v->paths = ft_split(line, ':');
	if (!v->paths | !v->paths[0])
		return (ft_leave(__FALLOC, PRINT_ERROR));
	if (!ft_rm_path(v))
		return (__FALSE);
	while (v->paths[i])
	{
		line = v->paths[i];
		v->paths[i] = ft_strjoin(v->paths[i], "/");
		if (!v->paths[i])
		{
			v->paths[i] = line;
			return (ft_leave(__FALLOC, PRINT_ERROR));
		}
		free(line);
		i++;
	}
	return (__TRUE);
}

char	*ft_getlinepath(t_vars *v)
{
	char	*line;
	int		i;

	i = 0;
	line = NULL;
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
		return (ft_leave(__FALLOC, PRINT_ERROR));
	free(v->paths[0]);
	v->paths[0] = str[1];
	str[1] = NULL;
	ft_free2str(&str);
	return (__TRUE);
}
