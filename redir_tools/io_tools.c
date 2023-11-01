/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 20:44:39 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/30 20:50:26 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
* ft_set_io() defines the standard input and standard output of the command
* to be executed by opening and closing the input/output specified on the 
* command line in order. So the last entry (file or HEREDOC) indicated on the
* command line becomes the standard input and so on for the standard output.

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
			fdbk = fdbk && ft_heredocredir(v, command);
		else if (!ft_strncmp(iterator->content, ">>", 3))
			fdbk = fdbk && ft_outappendredir(v, iterator->next->content);
		iterator = iterator->next->next;
		if (!fdbk)
			return (__FALSE);
	}
	ft_fclose(v, &command->hdoc_fd);
	return (__TRUE);
}

t_bool	ft_ioset_op(t_vars *v, int *infd, int *outfd)
{
	if (*infd > -1)
	{
		if (close(STDIN_FILENO) == -1)
			return (ft_leave(v, EXIT_FAILURE, "close STDIN_FILENO", __PERROR));
		if (dup(*infd) == -1)
			return (ft_leave(v, EXIT_FAILURE, "dup infd", __PERROR));
		if (!ft_fclose(v, infd))
			return (ft_leave(v, v->exitstatus, "close infd", __PRINT));
	}
	if (*outfd > -1)
	{
		if (close(STDOUT_FILENO) == -1)
			return (ft_leave(v, EXIT_FAILURE, "close STDOUT_FILENO", __PERROR));
		if (dup(*outfd) == -1)
			return (ft_leave(v, EXIT_FAILURE, "dup outfd", __PERROR));
		if (!ft_fclose(v, outfd))
			return (ft_leave(v, v->exitstatus, "close outfd", __PRINT));
	}
	return (__TRUE);
}
