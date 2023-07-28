/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setcmdpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/26 14:53:10 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_spthson(t_vars *v, char *cmd);
t_bool	ft_chck_cmd(t_vars *v, char *cmd, int i);
t_bool	ft_exitson(t_vars *v);
t_bool	ft_scp_op(t_vars *v, char *path);
t_bool	ft_cmdnfnd(t_vars *v);

int	ft_set_cmdpath(t_vars *v)
{
	int	i;

	i = 0;
	v->exit_code = EXIT_SUCCESS;
	if (!v->argv[0])
		return (__TRUE);
	if (!v->argv[0][0])
		return (ft_goprompt("command '' not found", __PRINT), __SKIP);
	if (!ft_chck_cmd(v, v->argv[0], i))
		return (__FALSE);
	if (v->exit_code != __EXIT_REACHED)
		return (ft_scp_op(v, ""));
	while (v->paths[i])
	{
		ft_freestr(&v->cmdpath);
		v->cmdpath = ft_strjoin(v->paths[i], v->argv[0]);
		if (!ft_chck_cmd(v, v->cmdpath, i))
			return (__FALSE);
		if (v->exit_code != __EXIT_REACHED)
			return (__TRUE);
		i++;
	}
	return (ft_cmdnfnd(v));
}

t_bool	ft_chck_cmd(t_vars *v, char *cmd, int i)
{
	int		pid;

	pid = -1;
// if (!cmd)
// 	return (ft_perror(v, EXIT_FAILURE, "plausible failed malloc()", __PRINT));
	v->exit_code = EXIT_FAILURE;
	pid = fork();
	if (pid == -1)
		return (ft_goprompt("fork", __PERROR));
	if (!pid)
		ft_spthson(v, cmd);
	if (!ft_pwait(v, pid, __WHANG))
		return (__FALSE);
	if (v->exit_code != __EXIT_REACHED)
		return (ft_scp_op(v, v->paths[i]));
	return (__TRUE);
}

void	ft_spthson(t_vars *v, char *cmd)
{
	char	**arg;

	v->p1[0] = -111;
	v->p1[1] = -111;
	v->p2[0] = -111;
	v->p2[1] = -111;
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
	execve(cmd, arg, __environ);
	ft_free2str(&arg);
	ft_exitson(v);
}

t_bool	ft_exitson(t_vars *v)
{
	ft_fclose(&v->p1[0]);
	ft_fclose(&v->p1[1]);
	ft_fclose(&v->p2[0]);
	ft_fclose(&v->p2[1]);
	ft_exitprocss(v, __EXIT_REACHED);
	return (__FALSE);
}

t_bool	ft_scp_op(t_vars *v, char *path)
{
	if (v->cmdpath)
		free(v->cmdpath);
	if (path[0])
		v->cmdpath = ft_strjoin(path, v->argv[0]);
	else
		v->cmdpath = ft_strdup(v->argv[0]);
	if (!v->cmdpath)
		return (ft_goprompt("plausible failed malloc()", __PRINT));
	return (__TRUE);
}
