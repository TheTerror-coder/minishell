/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getvalidpaths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:02:30 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/29 21:27:37 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_add_slash(t_vars *v);

t_bool	ft_set_path_variable(t_vars *v)
{
	char	*line;

	if (!check_env_var_set(v->my_env, "PATH"))
		return (ft_free2str(&v->paths), __TRUE);
	line = get_env_var_content(v, v->my_env, "PATH");
	if (!line)
		return (__FALSE);
	v->paths = ft_split(line, ':');
	free(line);
	if (!v->paths | !v->paths[0])
		return (ft_leave(v, EXIT_FAILURE, \
			"ft_set_path_variable() : ft_split() failed", __PRINT));
	if (!ft_add_slash(v))
		return (__FALSE);
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
			return (ft_leave(v, EXIT_FAILURE, \
				"ft_rm_path(): ft_strjoin() failed", __PRINT));
		}
		free(line);
		i++;
	}
	return (__TRUE);
}
