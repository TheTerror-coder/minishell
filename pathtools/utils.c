/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 19:12:23 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/11 20:20:30 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_fwait(t_vars *v, int pid, int option)
{
	int	ret;

	ret = waitpid(pid, &v->status, option);
	if (ret == -1)
		return (ft_goprompt("waitpid", __PERROR));
	if (ret == pid)
		if (WIFEXITED(v->status))
			v->exit_code = WEXITSTATUS(v->status);
	return (__TRUE);
}

t_bool	ft_fclose(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
			return (__FALSE);
		*fd = -111;
	}
	return (__TRUE);
}

t_bool	ft_ioset_op(int *infd, int *outfd)
{
	if (*infd > -1)
	{
		if (close(STDIN_FILENO) == -1)
			return (ft_goprompt("close STDIN_FILENO", __PERROR));
		if (dup(*infd) == -1)
			return (ft_goprompt("dup infd", __PERROR));
		if (!ft_fclose(infd))
			return (ft_goprompt("close infd", __PRINT));
	}
	if (*outfd > -1)
	{
		if (close(STDOUT_FILENO) == -1)
			return (ft_goprompt("close STDOUT_FILENO", __PERROR));
		if (dup(*outfd) == -1)
			return (ft_goprompt("dup outfd", __PERROR));
		if (!ft_fclose(outfd))
			return (ft_goprompt("close outfd", __PRINT));
	}
	return (__TRUE);
}

t_bool	ft_cmdnfnd(t_vars *v)
{
	write (STDERR_FILENO, v->argv[0], ft_strlen(v->argv[0]));
	if (!ft_strchr(v->argv[0], '/'))
		ft_goprompt(": command not found", __PRINT);
	else
		ft_goprompt(": No such file or directory", __PRINT);
	free(v->cmdpath);
	v->cmdpath = NULL;
	return (__SKIP);
}
