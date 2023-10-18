/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/18 16:11:36 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_cmdnfnd(char *command);
char	*ft_try_find_the_path(t_vars *v, char *command);

char	*ft_set_cmdpath(t_vars *v, char *command)
{
	if (!command)
		return (NULL);
	if (!command[0])
		return (ft_goprompt("command '' not found", __PRINT), NULL);
	if (!access(command, X_OK))
		return (ft_strdup(command));
	return (ft_try_find_the_path(v, command));
}

char	*ft_try_find_the_path(t_vars *v, char *command)
{
	int	i;

	i = 0;
	while (v->paths[i])
	{
		ft_freestr(&v->str);
		v->str = ft_strjoin(v->paths[i], command);
		if (!access(v->str, X_OK))
			return (ft_strdup(v->str));
		i++;
	}
	return (ft_cmdnfnd(command), NULL);
}

t_bool	ft_cmdnfnd(char *command)
{
	write (STDERR_FILENO, command, ft_strlen(command));
	if (!ft_strchr(command, '/'))
		ft_goprompt(": command not found", __PRINT);
	else
		ft_goprompt(": No such file or directory", __PRINT);
	return (__SKIP);
}
