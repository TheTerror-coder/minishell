/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/22 17:07:32 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_cmdnfnd(char *command);
char	*ft_try_find_the_path(t_vars *v, char *command);

char	*ft_set_cmdpath(t_vars *v, char *command)
{
	if (!command)
		return (exitstatus = EXIT_SUCCESS, NULL);
	if (!command[0])
		return (ft_leave(__CMD_NOT_FOUND, \
				"command '' not found", __PRINT), NULL);
	if (!access(command, X_OK))
		return (ft_strdup(command));
	if (!ft_set_path_variable(v))
		return (NULL);
	return (ft_try_find_the_path(v, command));
}

char	*ft_try_find_the_path(t_vars *v, char *command)
{
	int	i;

	i = 0;
	while (v->paths && v->paths[i])
	{
		ft_freestr(&v->str);
		v->str = ft_strjoin(v->paths[i], command);
		if (!v->str)
			return (ft_leave(EXIT_FAILURE, \
			"ft_try_find_the_path(): ft_strjoin() failed", __PRINT), NULL);
		if (!access(v->str, X_OK))
			return (ft_strdup(v->str));
		i++;
	}
	return (ft_cmdnfnd(command), NULL);
}

t_bool	ft_cmdnfnd(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	if (!ft_strchr(command, '/'))
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	exitstatus = __CMD_NOT_FOUND;
	return (__FALSE);
}
