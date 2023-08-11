/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/10 17:06:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_spth_son(t_vars *v, char *cmd);
t_bool	ft_chckcmd(t_vars *v, char *cmd, int i);
t_bool	ft_exitson0(t_vars *v, int *p);
t_bool	ft_op_scp(t_vars *v, char *path);
int		ft_cmdnotfnd(t_vars *v);

int	ft_setcmdpath(t_vars *v)
{
	t_ppex	*var;
	int		i;

	var = v->var;
	i = 0;
	exitstatus = EXIT_SUCCESS;
	if (!var->cmdlst[var->i])
		return (ft_perror(EXIT_FAILURE, \
			"command '' not found", __PRINT), __SKIP);
	if (!ft_chckcmd(v, var->cmdlst[var->i][0], i))
		return (__FALSE);
	if (exitstatus != __EXIT_NOCMD)
		return (ft_op_scp(v, ""));
	while (v->paths[i])
	{
		ft_freestr(&var->pathcmd);
		var->pathcmd = ft_strjoin(v->paths[i], var->cmdlst[var->i][0]);
		if (!ft_chckcmd(v, var->pathcmd, i))
			return (__FALSE);
		if (exitstatus != __EXIT_NOCMD)
			return (__TRUE);
		i++;
	}
	return (ft_cmdnotfnd(v));
}

t_bool	ft_chckcmd(t_vars *v, char *cmd, int i)
{
	int		pid;

	if (!cmd)
		return (ft_perror(EXIT_FAILURE, \
						"plausible failed malloc()", __PRINT));
	exitstatus = EXIT_FAILURE;
	pid = fork();
	if (pid == -1)
		return (ft_perror(EXIT_FAILURE, "fork", __PERROR));
	if (!pid)
		ft_spth_son(v, cmd);
	if (!ft_fwait(v, pid, __WHANG))
		return (__FALSE);
	if (exitstatus != __EXIT_NOCMD)
	{
		return (ft_op_scp(v, v->paths[i]));
	}
	return (__TRUE);
}

void	ft_spth_son(t_vars *v, char *cmd)
{
	t_ppex	*var;
	int		p[2];
	char	**name;

	var = v->var;
	p[0] = -111;
	p[1] = -111;
	if (pipe(var->sp) == -1)
		ft_exitson0(v, p);
	if (pipe(p) == -1)
		ft_exitson0(v, p);
	if (!ft_ioset_op(&var->sp[0], &var->sp[1]))
		ft_exitson0(v, p);
	if (!ft_ioset_op(&var->sp[0], &p[1]))
		ft_exitson0(v, p);
	if (close(STDERR_FILENO) == -1)
		ft_exitson0(v, p);
	name = ft_split(var->cmdlst[var->i][0], ' ');
	if (!name)
		ft_exitson0(v, p);
	execve(cmd, name, __environ);
	ft_freesplit(name);
	ft_exitson0(v, p);
}

t_bool	ft_exitson0(t_vars *v, int *p)
{
	ft_fclose(&p[0]);
	ft_fclose(&p[1]);
	ft_exitpipe(__EXIT_NOCMD, v);
	return (__FALSE);
}

t_bool	ft_op_scp(t_vars *v, char *path)
{
	t_ppex	*var;

	var = v->var;
	ft_freestr(&var->pathcmd);
	if (path[0])
		var->pathcmd = ft_strjoin(path, var->cmdlst[var->i][0]);
	else
		var->pathcmd = ft_strdup(var->cmdlst[var->i][0]);
	if (!var->pathcmd)
		return (ft_perror(EXIT_FAILURE, \
						"plausible failed malloc()", __PRINT));
	return (__TRUE);
}
