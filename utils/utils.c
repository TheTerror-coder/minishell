/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:10:06 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/20 15:11:48 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_goprompt(char *msg, t_typ action)
{
	exitstatus = EXIT_FAILURE;
	if (!msg)
		return (__FALSE);
	// ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (action == PRINT_ERROR)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	return (__FALSE);
}

t_bool	ft_leave(char *msg, t_typ action)
{
	exitstatus = EXIT_FAILURE;
	if (!msg)
		return (__FALSE);
	// ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (action == PRINT_ERROR)
		ft_putendl_fd(msg, STDERR_FILENO);
	else
		perror(msg);
	return (__FALSE);
}

t_bool	ft_isseperator(char c, char *suite)
{
	if (c == ' ' || c == '\t')
		return (__TRUE);
	if (c == "'"[0])
	{
		if (ft_strchr(suite, "'"[0]))
			return (__TRUE);
		return (__FALSE);
	}
	if (c == '"') 
	{
		if (ft_strchr(suite, '"'))
			return (__TRUE);
		return (__FALSE);
	}
	return (__FALSE);
}

void	ft_skip_partquoted(char *line, int *i)
{
	char	c;

	c = line[*i];
	*i = *i + 1;
	while (line[*i] != c)
		*i = *i + 1;
}

char	*ft_setofquote(t_vars *v, char c)
{
	char	*set;

	set = ft_calloc(2, sizeof(char));
	if (!set)
		return (NULL);
	set[0] = c;
	set[1] = 0;
	if (v->set)
		free(v->set);
	v->set = set;
	return (set);
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

t_bool	ft_raz(t_vars *v)
{
	int	in;
	int	out;

	in = __CLOSED_FD;
	out = __CLOSED_FD;
	v->flg_exit_main_procss = __FALSE;
	in = dup(v->stdin);
	out = dup(v->stdout);
	if (out < 0 || in < 0)
		perror("dup");
	ft_ioset_op(&in, &out);
	return (__TRUE);
}
