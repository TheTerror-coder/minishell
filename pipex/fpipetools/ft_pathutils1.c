/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathutils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/05/08 17:44:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipetools.h"

t_bool	ft_ioset_op(t_vars *var, int *infd, int *outfd);
void	ft_spthson(t_vars *var, char *cmd);
t_bool	ft_chck_cmd(t_vars *var, char *cmd, int i);
t_bool	ft_exitson(t_vars *var, int *p);
t_bool	ft_scp_op(t_vars *var, char *path);
t_bool	ft_cmdnfnd(t_vars *var);

int	ft_setcmdpath(t_vars *var)
{
	int	i;

	i = 0;
	var->exit = EXIT_SUCCESS;
	if (!var->cmdlst[var->i])
	{
		ft_perror(var, EXIT_FAILURE, "command '' not found", __PRINT);
		return (__SKIP);
	}
	if (!ft_chck_cmd(var, var->cmdlst[var->i][0], i))
		return (__FALSE);
	if (var->exit != __EXIT_NOCMD)
		return (ft_scp_op(var, ""));
	while (var->paths[i])
	{
		if (var->cmdpath)
			free(var->cmdpath);
		var->cmdpath = ft_strjoin(var->paths[i], var->cmdlst[var->i][0]);
		if (!ft_chck_cmd(var, var->cmdpath, i))
			return (__FALSE);
		if (var->exit != __EXIT_NOCMD)
			return (__TRUE);
		i++;
	}
	return (ft_cmdnfnd(var));
}

t_bool	ft_chck_cmd(t_vars *var, char *cmd, int i)
{
	int		pid;

	if (!cmd)
		return (ft_perror(var, EXIT_FAILURE, \
						"plausible failed malloc()", __PRINT));
	var->exit = EXIT_FAILURE;
	pid = fork();
	if (pid == -1)
		return (ft_perror(var, EXIT_FAILURE, "fork", __PERROR));
	if (!pid)
		ft_spthson(var, cmd);
	if (!ft_fwait(var, pid, __WHANG))
		return (__FALSE);
	if (var->exit != __EXIT_NOCMD)
		return (ft_scp_op(var, var->paths[i]));
	return (__TRUE);
}

void	ft_spthson(t_vars *var, char *cmd)
{
	int		p[2];
	char	**name;

	p[0] = -111;
	p[1] = -111;
	if (pipe(var->sp) == -1)
		ft_exitson(var, p);
	if (pipe(p) == -1)
		ft_exitson(var, p);
	if (!ft_ioset_op(var, &var->sp[0], &var->sp[1]))
		ft_exitson(var, p);
	if (!ft_ioset_op(var, &var->sp[0], &p[1]))
		ft_exitson(var, p);
	if (close(STDERR_FILENO) == -1)
		ft_exitson(var, p);
	name = ft_split(var->cmdlst[var->i][0], ' ');
	if (!name)
		ft_exitson(var, p);
	execve(cmd, name, __environ);
	ft_freesplit(name);
	ft_exitson(var, p);
}

t_bool	ft_exitson(t_vars *var, int *p)
{
	ft_fclose(&p[0]);
	ft_fclose(&p[1]);
	ft_exitprocss(__EXIT_NOCMD, var);
	return (__FALSE);
}

t_bool	ft_scp_op(t_vars *var, char *path)
{
	if (var->cmdpath)
		free(var->cmdpath);
	if (path[0])
		var->cmdpath = ft_strjoin(path, var->cmdlst[var->i][0]);
	else
		var->cmdpath = ft_strdup(var->cmdlst[var->i][0]);
	if (!var->cmdpath)
		return (ft_perror(var, EXIT_FAILURE, \
						"plausible failed malloc()", __PRINT));
	return (__TRUE);
}

/*
**void	ft_spthson(t_vars *var);
**t_bool	ft_spthfather(t_vars *var, int pid);
**t_bool	ft_getpath(t_vars *var);
**
**int	ft_setpath(t_vars *var)
**{
**	int		pid;
**
**	var->exit = EXIT_SUCCESS;
**	if (!var->cmdlst[var->i])
**	{
**		ft_perror(var, EXIT_FAILURE, "command '' not found", __PRINT);
**		return (__SKIP);
**	}
**	if (pipe(var->sp) == -1)
**		return (ft_perror(var, EXIT_FAILURE, "pipe", __PERROR));
**	if (!ft_setwch(var))
**		return (__FALSE);
**	pid = fork();
**	if (!pid)
**		ft_spthson(var);
**	else if (pid == -1)
**		return (ft_perror(var, EXIT_FAILURE, "fork", __PERROR));
**	return (ft_spthfather(var, pid));
**}
**
**void	ft_spthson(t_vars *var)
**{
**	if (close(STDOUT_FILENO) == -1)
**		ft_exitprocss(EXIT_FAILURE, var);
**	if (dup(var->sp[1]) == -1)
**		ft_exitprocss(EXIT_FAILURE, var);
**	if (!ft_fclose(&var->sp[1]))
**		ft_exitprocss(EXIT_FAILURE, var);
**	if (!ft_fclose(&var->sp[0]))
**		ft_exitprocss(EXIT_FAILURE, var);
**	execve("/usr/bin/which", var->awhich, __environ);
**	perror("execve");
**	ft_exitprocss(EXIT_FAILURE, var);
**}
**
**t_bool	ft_spthfather(t_vars *var, int pid)
**{
**	int		len;
**	int		i;
**	char	c;
**
**	i = 0;
**	c = 0;
**	if (!ft_fclose(&var->sp[1]))
**		return (__FALSE);
**	if (var->cmdpath)
**		free(var->cmdpath);
**	var->cmdpath = ft_calloc(__MXPATH, sizeof (char));
**	if (!var->cmdpath)
**		return (ft_perror(var, EXIT_FAILURE, "ft_calloc() failed", __PRINT));
**	len = read(var->sp[0], &c, 1);
**	while (len > 0 && ft_isprint(c) && i < __MXPATH)
**	{
**		var->cmdpath[i] = c;
**		i++;
**		len = read(var->sp[0], &c, 1);
**	}
**	if (!ft_fwait(var, pid, __WHANG))
**		return (__FALSE);
**	if (len < 0)
**		return (ft_perror(var, EXIT_FAILURE, "read", __PERROR));
**	return (ft_getpath(var));
**}
**
**t_bool	ft_getpath(t_vars *var)
**{
**	if (!ft_strlen(var->cmdpath) && var->exit != EXIT_SUCCESS)
**	{
**		write (STDERR_FILENO, var->cmdlst[var->i][0], \
**				ft_strlen(var->cmdlst[var->i][0]));
**		ft_perror(var, var->exit, ": command not found", __PRINT);
**		if (!ft_fclose(&var->sp[0]))
**			return (__FALSE);
**		return (__SKIP);
**	}
**	return (ft_fclose(&var->sp[0]));
**}
*/