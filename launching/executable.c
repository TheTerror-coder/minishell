/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:08:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/10 16:57:28 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_execute(t_vars *v);

t_bool	ft_set_io(t_vars *v)
{
	int	nada;
	t_bool fdbk;

	nada = -111;
	fdbk = __TRUE;
	if (v->flg_infile)
	{
		if (access(v->infile, R_OK))
			return (ft_goprompt(v->infile, __PERROR));
		fdbk = fdbk & ft_inredir(v, &nada);
	}
	if (v->flg_outfile)
		fdbk = fdbk & ft_outredir(v, &nada);
	if (v->flg_heredoc)
		fdbk = fdbk & ft_heredocredir(v, &nada);
	if (v->flg_outappend)
		fdbk = fdbk & ft_outappendredir(v, &nada);
	return (fdbk);
}

t_bool	ft_lnch_executable(t_vars *v)
{
	int	pid;

	pid = -1;
	pid = fork();
	if (pid < 0)
		return (ft_goprompt("fork", __PERROR));
	if (!pid)
		ft_execute(v);
	waitpid(pid, &v->status, __WHANG);
	if (WIFEXITED(v->status))
	{
		exitstatus = WEXITSTATUS(v->status);
		if (exitstatus!= EXIT_SUCCESS && exitstatus != __EXIT_REACHED)
			return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_execute(t_vars *v)
{
	char	*line;

	exitstatus = EXIT_SUCCESS;
	line = NULL;
	if (v->flg_pipeline)
		ft_pipeline(v, v->nb, v->lst);
	if (!ft_set_io(v))
		ft_exitprocss(v, exitstatus);
	if (v->flg_heredoc && !v->argv[0])
	{
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			ft_freestr(&line);
			line = get_next_line(STDIN_FILENO);
		}
		ft_freestr(&line);
		ft_exitprocss(v, EXIT_SUCCESS);
	}
	if (ft_set_cmdpath(v) != __TRUE)
		return (__FALSE);
	ft_freesecondaries(v);
	execve(v->cmdpath, v->argv, __environ);
	perror("execve");
	ft_exitprocss(v, __EXIT_REACHED);
	return (__FALSE);
}
