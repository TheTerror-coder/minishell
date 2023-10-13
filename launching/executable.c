/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:08:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/13 15:48:24 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_execute(t_vars *v);

/*
* This function first runs all HEREDOCS we have on a simple command line.
* Then it defines the standard input and standard output of the command
* to be executed by opening and closing the input/output specified on the 
* command line in order. So the last entry (file or HEREDOC) indicated on the
* command line becomes the standard input and so on for the standard output.
*
* At the end, Always close the heredoc file descriptor (v->hdoc_fd) otherwise 
* a the rear heredoc process will remain waiting.
*/
t_bool	ft_set_io(t_vars *v)
{
	t_token	*iterator;
	t_bool	fdbk;

	iterator = v->commands->tokens;
	while (iterator)
	{
		if (!ft_strncmp(iterator->content, "<<", 3))
			ft_launch_heredoc(v, iterator->next->content);
		iterator = iterator->next->next;
	}
	fdbk = __TRUE;
	iterator = v->commands->tokens;
	while (iterator)
	{
		if (!ft_strncmp(iterator->content, "<", 2))
			fdbk = fdbk && ft_inredir(v, iterator->next->content);
		else if (!ft_strncmp(iterator->content, ">", 2))
			fdbk = fdbk && ft_outredir(v, iterator->next->content);
		else if (!ft_strncmp(iterator->content, "<<", 3))
			fdbk = fdbk && ft_heredocredir(v);
		else if (!ft_strncmp(iterator->content, ">>", 3))
			fdbk = fdbk && ft_outappendredir(v, iterator->next->content);
		iterator = iterator->next->next;
		if (!fdbk)
			return (__FALSE);
	}
	ft_fclose(&v->hdoc_fd);
	return (__TRUE);
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
	// if (v->flg_pipeline)
	// 	ft_pipeline(v, v->nb, v->lst);
	if (!ft_set_io(v))
		ft_exitbackprocss(v, exitstatus);
	if (v->flg_heredoc && !v->argv[0])
	{
		line = get_next_line(STDIN_FILENO);
		while (line)
		{
			ft_freestr(&line);
			line = get_next_line(STDIN_FILENO);
		}
		ft_freestr(&line);
		ft_exitbackprocss(v, EXIT_SUCCESS);
	}
	if (ft_set_cmdpath(v, v->commands->arguments) != __TRUE)
		return (__FALSE);
	ft_freesecondaries(v);
	execve(v->cmdpath, v->commands->arguments, __environ);
	perror("execve");
	ft_exitbackprocss(v, __EXIT_REACHED);
	return (__FALSE);
}
