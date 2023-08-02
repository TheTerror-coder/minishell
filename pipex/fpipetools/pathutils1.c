/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathutils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:53:58 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/02 17:02:20 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

t_bool	ft_op_ioset(t_vars *v, int *infd, int *outfd);
void	ft_spth_son(t_vars *v, char *cmd);
t_bool	ft_chckcmd(t_vars *v, char *cmd, int i);
t_bool	ft_exitson0(t_vars *v, int *p);
t_bool	ft_op_scp(t_vars *v, char *path);
t_bool	ft_cmdnotfnd(t_vars *v);

int	ft_setcmdpath(t_vars *v)
{
	t_ppex	*var;
	int		i;

	var = v->var;
	i = 0;
	var->exit = EXIT_SUCCESS;
	if (!var->cmdlst[var->i])
		return (ft_perror(v, EXIT_FAILURE, \
			"command '' not found", __PRINT), __SKIP);
	if (!ft_chckcmd(v, var->cmdlst[var->i][0], i))
		return (__FALSE);
	if (var->exit != __EXIT_NOCMD)
		return (ft_op_scp(v, ""));
	while (var->paths[i])
	{
		ft_freestr(&var->pathcmd);
		var->pathcmd = ft_strjoin(var->paths[i], var->cmdlst[var->i][0]);
		if (!ft_chckcmd(v, var->pathcmd, i))
			return (__FALSE);
		if (var->exit != __EXIT_NOCMD)
			return (__TRUE);
		i++;
	}
	return (ft_cmdnotfnd(v));
}

t_bool	ft_chckcmd(t_vars *v, char *cmd, int i)
{
	t_ppex	*var;
	int		pid;

	var = v->var;
	if (!cmd)
		return (ft_perror(v, EXIT_FAILURE, \
						"plausible failed malloc()", __PRINT));
	var->exit = EXIT_FAILURE;
	pid = fork();
	if (pid == -1)
		return (ft_perror(v, EXIT_FAILURE, "fork", __PERROR));
	if (!pid)
		ft_spth_son(v, cmd);
	if (!ft_fwait(v, pid, __WHANG))
		return (__FALSE);
	if (var->exit != __EXIT_NOCMD)
		return (ft_op_scp(v, var->paths[i]));
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
	if (!ft_op_ioset(v, &var->sp[0], &var->sp[1]))
		ft_exitson0(v, p);
	if (!ft_op_ioset(v, &var->sp[0], &p[1]))
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
	ft_fclose0(&p[0]);
	ft_fclose0(&p[1]);
	ft_exitpipe(__EXIT_NOCMD, v);
	return (__FALSE);
}

t_bool	ft_op_scp(t_vars *v, char *path)
{
	t_ppex	*var;

	var = v->var;
	if (var->pathcmd)
		free(var->pathcmd);
	if (path[0])
		var->pathcmd = ft_strjoin(path, var->cmdlst[var->i][0]);
	else
		var->pathcmd = ft_strdup(var->cmdlst[var->i][0]);
	if (!var->pathcmd)
		return (ft_perror(v, EXIT_FAILURE, \
						"plausible failed malloc()", __PRINT));
	return (__TRUE);
}
