/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:53:24 by TheTerror         #+#    #+#             */
/*   Updated: 2023/07/26 00:37:35 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_heredoc_op1(t_vars *v);
t_bool	ft_heredoc_op2(t_vars *v);
t_bool	ft_openatemp(t_vars *v);
t_bool	ft_heredocredir2(t_vars *v);

t_bool	ft_heredocredir(t_vars *v)
{
	int	pid;

	pid = 0;
	v->exit_code = EXIT_SUCCESS;
	ft_openatemp(v);
	pid = fork();
	if (pid == -1)
		ft_exitprocss(v, !ft_goprompt("fork", PRINT_ERROR));
	if (pid == 0)
		if (!ft_heredoc_op1(v))
			ft_exitprocss(v, EXIT_FAILURE);
	if (!ft_pwait(v, pid, 0))
		ft_exitprocss(v, EXIT_FAILURE);
	if (pipe(v->p1) == -1)
		ft_exitprocss(v, !ft_goprompt("pipe", PRINT_ERROR));
	ft_heredocredir2(v);
	return (__TRUE);
}

t_bool	ft_heredocredir2(t_vars *v)
{
	int	pid;

	pid = 0;
	v->exit_code = EXIT_SUCCESS;
	pid = fork();
	if (pid == -1)
		ft_exitprocss(v, !ft_goprompt("fork", PRINT_ERROR));
	if (pid == 0)
		if (!ft_heredoc_op2(v))
			ft_exitprocss(v, EXIT_FAILURE);
	ft_fclose(&v->outfd);
	ft_fclose(&v->p1[1]);
	if (!ft_ioset_op(&v->p1[0], &v->p1[1]))
		ft_exitprocss(v, EXIT_FAILURE);
	if (!ft_pwait(v, pid, WNOHANG))
		ft_exitprocss(v, EXIT_FAILURE);
	return (__TRUE);
}

t_bool	ft_heredoc_op1(t_vars *v)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	while (ft_strncmp(line, v->limiter, ft_strlen(line) + ft_strlen(v->limiter)))
	{
		ft_putendl_fd(line, v->outfd);
		ft_freestr(&line);
		line = readline("> ");
	}
	ft_freestr(&line);
	ft_fclose(&v->outfd);
	ft_exitprocss(v, __SUCCEED);
	return (__FALSE);
}

t_bool	ft_heredoc_op2(t_vars *v)
{
	char	*line;

	line = NULL;
	ft_fclose(&v->p1[0]);
	ft_fclose(&v->infd);
	ft_fclose(&v->outfd);
	v->infd = open(v->ftemp1, O_RDONLY);
	if (v->infd == -1)
		ft_exitprocss(v, !ft_goprompt(v->ftemp1, __PERROR));
	if (!ft_ioset_op(&v->infd, &v->outfd))
		ft_exitprocss(v, EXIT_FAILURE);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		ft_putstr_fd(line, v->p1[1]);
		ft_freestr(&line);
		line = get_next_line(STDIN_FILENO);
	}
	ft_freestr(&line);
	ft_exitprocss(v, EXIT_SUCCESS);
	return (__FALSE);
}

t_bool	ft_setftemp(t_vars *v, int n)
{
	char	*strnum;

	strnum = NULL;
	if (v->ftemp1)
		free(v->ftemp1);
	v->ftemp1 = NULL;
	strnum = ft_itoa(n);
	if (!strnum)
		ft_exitprocss(v, !ft_goprompt("failed allocation", PRINT_ERROR));
	v->ftemp1 = ft_strjoin(__RADICAL, strnum);
	if (!v->ftemp1)
	{
		free(strnum);
		ft_exitprocss(v, !ft_goprompt("failed allocation", PRINT_ERROR));
	}
	return (__TRUE);
}

t_bool	ft_openatemp(t_vars *v)
{
	int		n;
	
	n = 9999999;
	ft_setftemp(v, n);
	while (n > 0 && !access(v->ftemp1, F_OK))
	{
		n--;
		ft_setftemp(v, n);
	}
	if (!n)
		ft_exitprocss(v, !ft_goprompt("temp file already exits", PRINT_ERROR));
	ft_fclose(&v->outfd);
	v->outfd = open(v->ftemp1, O_CREAT | O_WRONLY | O_TRUNC, \
					S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR | S_IWGRP);
	if (v->outfd == -1)
		ft_exitprocss(v, !ft_goprompt(v->ftemp1, __PERROR));
	return (__TRUE);
}
