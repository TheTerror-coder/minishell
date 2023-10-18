/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/17 23:50:03 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_spthson(t_vars *v, char *cmd);
t_bool	ft_chck_cmd(t_vars *v, char **argv, char *cmd, int i);
t_bool	ft_path_is_included(t_vars *v, char **argv, int i);
t_bool	ft_try_find_the_path(t_vars *v, char **argv, int i);
t_bool	ft_exitson(t_vars *v);
t_bool	ft_scp_op(t_vars *v, char **argv, char *path);
t_bool	ft_cmdnfnd(t_vars *v, char *command);

char	*ft_set_cmdpath(t_vars *v, char **argv)
{
	char	*cmd_path;
	int	i;

	i = 0;
	v->exit_code = EXIT_SUCCESS;
	if (!argv[0])
		return (NULL);
	if (!argv[0][0])
		return (ft_goprompt("command '' not found", __PRINT), NULL);
	if (ft_path_is_included(v, argv, i))
	{
		cmd_path = v->str;
		return (v->str = NULL, cmd_path);
	}
	if (ft_try_find_the_path(v, argv, i))
	{
		cmd_path = v->str;
		return (v->str = NULL, cmd_path);
	}
	return (ft_cmdnfnd(v, argv[0]), NULL);
}

t_bool	ft_path_is_included(t_vars *v, char **argv, int i)
{
	if (!ft_chck_cmd(v, argv, argv[0], i))
		return (__FALSE);
	if (v->exit_code != __EXIT_REACHED)
		return (ft_scp_op(v, argv, ""));
	return (__FALSE);
}

t_bool	ft_try_find_the_path(t_vars *v, char **argv, int i)
{
	while (v->paths[i])
	{
		ft_freestr(&v->str);
		v->str = ft_strjoin(v->paths[i], argv[0]);
		if (!ft_chck_cmd(v, argv, v->str, i))
			return (__FALSE);
		if (v->exit_code != __EXIT_REACHED)
			return (__TRUE);
		i++;
	}
	return (__FALSE);
}

t_bool	ft_chck_cmd(t_vars *v, char **argv, char *cmd, int i)
{
	int		pid;

	pid = -1;
	v->exit_code = EXIT_FAILURE;
	pid = fork();
	if (pid == -1)
		return (ft_goprompt("fork", __PERROR));
	if (!pid)
		ft_spthson(v, cmd);
	if (!ft_pwait(v, pid, __WHANG))
		return (__FALSE);
	if (v->exit_code != __EXIT_REACHED)
		return (ft_scp_op(v, argv, v->paths[i]));
	return (__TRUE);
}

void	ft_spthson(t_vars *v, char *cmd)
{
	char	**arg;

	v->p1[0] = __CLOSED_FD;
	v->p1[1] = __CLOSED_FD;
	v->p2[0] = __CLOSED_FD;
	v->p2[1] = __CLOSED_FD;
	if (pipe(v->p1) == -1)
		ft_exitson(v);
	if (pipe(v->p2) == -1)
		ft_exitson(v);
	if (!ft_ioset_op(&v->p1[0], &v->p1[1]))
		ft_exitson(v);
	if (!ft_ioset_op(&v->p1[0], &v->p2[1]))
		ft_exitson(v);
	if (close(STDERR_FILENO) == -1)
		ft_exitson(v);
	arg = ft_split(cmd, ' ');
	execve(cmd, arg, v->envp);
	ft_free2str(&arg);
	ft_exitson(v);
}

t_bool	ft_exitson(t_vars *v)
{
	ft_fclose(&v->p1[0]);
	ft_fclose(&v->p1[1]);
	ft_fclose(&v->p2[0]);
	ft_fclose(&v->p2[1]);
	ft_exitbackprocss(v, __EXIT_REACHED);
	return (__FALSE);
}

t_bool	ft_scp_op(t_vars *v, char **argv, char *path)
{
	ft_freestr(&v->str);
	if (path[0])
		v->str = ft_strjoin(path, argv[0]);
	else
		v->str = ft_strdup(argv[0]);
	if (!v->str)
		return (ft_goprompt("plausible failed malloc()", __PRINT));
	return (__TRUE);
}
