/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:08:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/08/03 23:15:25 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_execute(t_vars *v);

t_bool	ft_set_io(t_vars *v)
{
	if (v->flg_infile)
		ft_inredir(v);
	if (v->flg_outfile)
		ft_outredir(v);
	if (v->flg_heredoc)
		ft_heredocredir(v);
	if (v->flg_outappend)
		ft_outappendredir(v);
	return (__TRUE);
}

t_bool	ft_lnch_executable(t_vars *v)
{
	int	pid;

	if (ft_set_cmdpath(v) != __TRUE)
		return (__FALSE);
	pid = -1;
	pid = fork();
	if (pid < 0)
		return (ft_goprompt("fork", __PERROR));
	if (!pid)
		ft_execute(v);
	waitpid(pid, &v->status, 0);
	if (WIFEXITED(v->status))
	{
		v->exit_code = WEXITSTATUS(v->status);
		if (v->exit_code != EXIT_SUCCESS && v->exit_code != __EXIT_REACHED)
			return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_execute(t_vars *v)
{
	char	*line;

	line = NULL;
	ft_set_io(v);
	if (v->flg_pipeline)
		ft_pipeline(v, v->nb, v->lst);
	if (!v->argv[0])
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
	ft_freesecondaries(v);
	execve(v->cmdpath, v->argv, __environ);
	perror("execve");
	ft_exitprocss(v, __EXIT_REACHED);
	return (__FALSE);
}
