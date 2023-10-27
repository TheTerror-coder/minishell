/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/27 16:07:17 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_cmdnfnd(char *command);
t_bool	ft_cmd_has_dir_format(char *command, char *slash);
int		ft_cmd_has_file_format(char *command);
char	*ft_try_find_the_path(t_vars *v, char *command);

char	*ft_set_cmdpath(t_vars *v, char *command)
{
	char	*slash;
	int	fdbk;

	slash = NULL;
	if (!command)
		return (exitstatus = EXIT_SUCCESS, NULL);
	if (!command[0])
		return (ft_leave(__CMD_NOT_FOUND, \
				"command '' not found", __PRINT), NULL);
	fdbk = __CONTINUE;
	slash = ft_strrchr(command, '/');
	if (slash && slash[1])
		fdbk = ft_cmd_has_file_format(command);
	else if (slash && !slash[1])
		fdbk = ft_cmd_has_dir_format(command, slash);
	if (fdbk == __FALSE)
		return (NULL);
	if (fdbk == __TRUE)
		return (ft_strdup(command));
	if (!ft_set_path_variable(v))
		return (NULL);
	return (ft_try_find_the_path(v, command));
}

t_bool	ft_cmd_has_dir_format(char *command, char *slash)
{
	struct stat	__stat;

	stat(command, &__stat);
	if (S_ISDIR(__stat.st_mode))
		return (ft_leave(__CMD_NOT_FOUND, "Is a directory", __PRINT));
	*slash = '\0';
	if (!access(command, F_OK))
		ft_leave(__CMD_NOT_FOUND, "Not a directory", __PRINT);
	*slash = '/';
	(void) slash;
	return (__FALSE);
}

int	ft_cmd_has_file_format(char *command)
{
	struct stat	__stat;

	stat(command, &__stat);
	if (S_ISDIR(__stat.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		return (exitstatus = __CMD_NOT_EXEC, __FALSE);
	}
	else if (!access(command, F_OK))
	{
		if (!access(command, X_OK))
			return (__TRUE);
		else
			return (ft_leave(__CMD_NOT_EXEC, command, __PERROR));
	}
	exitstatus = 127;
	return (ft_leave(__CMD_NOT_FOUND, "No such file or directory", __PRINT));
}

char	*ft_try_find_the_path(t_vars *v, char *command)
{
	int	i;
	int	fdbk;

	i = 0;
	fdbk = 0;
	while (v->paths && v->paths[i])
	{
		ft_freestr(&v->str);
		v->str = ft_strjoin(v->paths[i], command);
		if (!v->str)
			return (ft_leave(EXIT_FAILURE, \
			"ft_try_find_the_path(): ft_strjoin() failed", __PRINT), NULL);
		if (!access(v->str, F_OK))
		{
			fdbk = access(v->str, X_OK);
			if (fdbk)
				return (ft_leave(__CMD_NOT_EXEC, v->str, __PERROR), NULL);
			else
				return (ft_strdup(v->str));
		}
		i++;
	}
	return (ft_cmdnfnd(command), NULL);
}

t_bool	ft_cmdnfnd(char *command)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	if (!ft_strrchr(command, '/'))
		ft_putendl_fd(": command not found", STDERR_FILENO);
	else
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	exitstatus = __CMD_NOT_FOUND;
	return (__FALSE);
}
