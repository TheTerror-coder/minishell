/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathutils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:02:30 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/04 18:27:13 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_getlinepath0(void);
t_bool	ft_rm_path0(t_vars *v);

t_bool	ft_setpath(t_vars *v)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_getlinepath0();
	if (!line)
		return (__FALSE);
	v->var->paths = ft_split(line, ':');
	if (!v->var->paths)
		return (__FALSE);
	if (!ft_rm_path0(v))
		return (__FALSE);
	while (v->var->paths[i])
	{
		line = v->var->paths[i];
		v->var->paths[i] = ft_strjoin(v->var->paths[i], "/");
		if (!v->var->paths[i])
		{
			v->var->paths[i] = line;
			return (__FALSE);
		}
		ft_freestr(&line);
		i++;
	}
	return (__TRUE);
}

char	*ft_getlinepath0(void)
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

t_bool	ft_rm_path0(t_vars *v)
{
	t_ppex	*var;
	char	**str;

	var = v->var;
	str = ft_split(var->paths[0], '=');
	if (!str)
		return (__FALSE);
	ft_freestr(&var->paths[0]);
	var->paths[0] = str[1];
	str[1] = NULL;
	ft_free2str(&str);
	return (__TRUE);
}
