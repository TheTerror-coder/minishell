/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initmem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:38:12 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/31 16:39:54 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_initfds(t_vars *v);
t_bool	init_my_env(t_vars *v);

t_vars	*ft_initvars(void)
{
	t_vars	*v;

	v = ft_calloc(1, sizeof(t_vars));
	if (!v)
		return (ft_leave(NULL, EXIT_FAILURE, "ft_calloc", __PERROR), NULL);
	if (!init_my_env(v))
		return (free(v), NULL);
	if (!ft_initfds(v))
	{
		free(v->my_env);
		return (free(v), NULL);
	}
	v->exitstatus = EXIT_SUCCESS;
	return (v);
}

t_bool	ft_initfds(t_vars *v)
{
	v->p1[0] = -111;
	v->p1[1] = -111;
	v->p2[0] = -111;
	v->p2[1] = -111;
	v->infd = -111;
	v->outfd = -111;
	v->stdin = -111;
	v->stdout = -111;
	v->stdin = dup(STDIN_FILENO);
	v->stdout = dup(STDOUT_FILENO);
	if (v->stdout < 0 || v->stdin < 0)
		return (ft_leave(NULL, EXIT_FAILURE, "dup", __PERROR), __FALSE);
	v->hdoc_fd = -111;
	return (__TRUE);
}

t_bool	init_my_env(t_vars *v)
{
	t_env	*env_list;

	env_list = malloc(sizeof(t_env));
	if (!env_list)
		return (ft_leave(v, EXIT_FAILURE, "malloc", __PERROR), __FALSE);
	env_list->var = NULL;
	env_list->next = NULL;
	v->my_env = env_list;
	return (__TRUE);
}
