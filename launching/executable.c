/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:08:55 by TheTerror         #+#    #+#             */
/*   Updated: 2023/11/03 14:27:36 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_execute(t_vars *v);
void	ft_run_simplecmnd(t_vars *v);

t_bool	ft_lnch_executable(t_vars *v)
{
	int	pid;

	ignore_signals();
	pid = fork();
	if (!pid)
		ft_execute(v);
	if (pid < 0)
		return (ft_leave(v, EXIT_FAILURE, "fork", __PERROR));
	v->code = EXIT_SUCCESS;
	waitpid(pid, &v->code, __WHANG);
	set_readline_signals();
	if (WIFEXITED(v->code) || WIFSIGNALED(v->code))
	{
		v->exitstatus = WEXITSTATUS(v->code);
		if (WIFSIGNALED(v->code))
		{
			v->exitstatus = 128 + WTERMSIG(v->code);
			if (v->exitstatus == 130)
				ft_putstr_fd("\n", 1);
		}
		if (v->exitstatus != EXIT_SUCCESS && v->exitstatus != __CMD_NOT_EXEC)
			return (__FALSE);
	}
	return (__TRUE);
}

t_bool	ft_execute(t_vars *v)
{
	if (v->commands && v->commands->next)
		ft_run_pipeline(v, v->commands);
	else
		ft_run_simplecmnd(v);
	return (__FALSE);
}

void	ft_run_simplecmnd(t_vars *v)
{
	char	**my_env;

	if (!ft_set_io(v, v->commands))
		ft_exitbackprocss(v, v->exitstatus);
	ft_freestr(&v->cmdpath);
	v->cmdpath = ft_set_cmdpath(v, v->commands->main_command);
	if (!v->cmdpath)
		ft_exitbackprocss(v, v->exitstatus);
	ft_closetvars(v);
	ft_freesecondaries(v);
	my_env = env_list_to_tab(v);
	if (!my_env && v->my_env->var)
		ft_exitbackprocss(v, v->exitstatus);
	execve(v->cmdpath, v->commands->arguments, my_env);
	perror("execve");
	ft_free2str(&my_env);
	ft_exitbackprocss(v, __CMD_NOT_EXEC);
}

/*
* This function runs all HEREDOCS we have on the command line and then ensures
* that the last remains opened so it can be read by the command.
*/
t_bool	ft_run_heredocs(t_vars *v, t_commands *command)
{
	t_commands	*cmd_iterator;
	t_token		*token_iterator;

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
					return (__FALSE);
			}
			token_iterator = token_iterator->next->next;
		}
		ft_fclose(v, &cmd_iterator->hdoc_fd);
		cmd_iterator->hdoc_fd = v->hdoc_fd;
		v->hdoc_fd = __CLOSED_FD;
		cmd_iterator = cmd_iterator->next;
	}
	return (__TRUE);
}
