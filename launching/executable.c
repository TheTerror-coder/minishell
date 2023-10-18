/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:08:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/17 23:50:03 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_execute(t_vars *v);
void	ft_run_simplecmnd(t_vars *v);
t_bool	ft_set_io(t_vars *v, t_commands *command);
t_bool	ft_run_heredocs(t_vars *v, t_commands *command);

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
		if (exitstatus != EXIT_SUCCESS && exitstatus != __EXIT_REACHED)
			return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_execute(t_vars *v)
{
	exitstatus = EXIT_SUCCESS;
	ft_run_heredocs(v, v->commands);
	if (v->commands && v->commands->next)
		ft_run_pipeline(v, v->commands);
	else
		ft_run_simplecmnd(v);
	return (__FALSE);
}

void	ft_run_simplecmnd(t_vars *v)
{
	if (!ft_set_io(v, v->commands))
		ft_exitbackprocss(v, exitstatus);
	ft_freestr(&v->cmdpath);
	v->cmdpath = ft_set_cmdpath(v, v->commands->arguments);
	if (!v->cmdpath)
		ft_exitbackprocss(v, EXIT_FAILURE);
	ft_freesecondaries(v);
	execve(v->cmdpath, v->commands->arguments, v->envp);
	perror("execve");
	ft_exitbackprocss(v, __EXIT_REACHED);
}

t_bool	ft_run_heredocs(t_vars *v, t_commands *command)
{
	t_commands	*cmd_iterator;
	t_token	*token_iterator;

	cmd_iterator = command;
	while (cmd_iterator)
	{
		token_iterator = cmd_iterator->tokens;
		while (token_iterator)
		{
			if (!ft_strncmp(token_iterator->content, "<<", 3))
			{
				v->flg_expand_in_hdoc = token_iterator->next->expand_in_hdoc;
				if (!ft_launch_heredoc(v, token_iterator->next->content))
					ft_exitbackprocss(v, EXIT_FAILURE);
			}
			token_iterator = token_iterator->next->next;
		}
		cmd_iterator->hdoc_fd = v->hdoc_fd;
		v->hdoc_fd = __CLOSED_FD;
		cmd_iterator = cmd_iterator->next;
	}
	return (__TRUE);
}

/*
* This function first runs all HEREDOCS we have on a simple command line.
* Then it defines the standard input and standard output of the command
* to be executed by opening and closing the input/output specified on the 
* command line in order. So the last entry (file or HEREDOC) indicated on the
* command line becomes the standard input and so on for the standard output.
*
* At the end, Always close the heredoc file descriptor (v->hdoc_fd) otherwise 
* the rear heredoc process will remain waiting.
*/
t_bool	ft_set_io(t_vars *v, t_commands *command)
{
	t_token	*iterator;
	t_bool	fdbk;

	fdbk = __TRUE;
	iterator = command->tokens;
	while (iterator)
	{
		if (!ft_strncmp(iterator->content, "<", 2))
			fdbk = fdbk && ft_inredir(v, iterator->next->content);
		else if (!ft_strncmp(iterator->content, ">", 2))
			fdbk = fdbk && ft_outredir(v, iterator->next->content);
		else if (!ft_strncmp(iterator->content, "<<", 3))
			fdbk = fdbk && ft_heredocredir(command);
		else if (!ft_strncmp(iterator->content, ">>", 3))
			fdbk = fdbk && ft_outappendredir(v, iterator->next->content);
		iterator = iterator->next->next;
		if (!fdbk)
			return (__FALSE);
	}
	ft_fclose(&command->hdoc_fd);
	return (__TRUE);
}
