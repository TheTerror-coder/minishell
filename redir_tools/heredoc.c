/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:53:24 by TheTerror         #+#    #+#             */
/*   Updated: 2023/10/15 01:51:21 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_bool	ft_heredoc_op1(t_vars *v);
t_bool	ft_heredoc_op2(t_vars *v);
t_bool	ft_heredoc2(t_vars *v);

t_bool	ft_heredoc(t_vars *v)
{
	int	pid;

	pid = -1;
	v->exit_code = EXIT_SUCCESS;
	ft_fclose(&v->hdoc_fd);
	ft_openatemp(v);
	pid = fork();
	if (pid < 0)
		return (ft_goprompt("fork", PRINT_ERROR));
	if (pid == 0)
		if (!ft_heredoc_op1(v))
			ft_exitbackprocss(v, EXIT_FAILURE);
	if (!ft_pwait(v, pid, __WHANG))
		return (__FALSE);
	if (pipe(v->p1) == -1)
		return (ft_goprompt("pipe", PRINT_ERROR));
	ft_heredoc2(v);
	return (__TRUE);
}

t_bool	ft_heredoc2(t_vars *v)
{
	int	pid;

	pid = 0;
	v->exit_code = EXIT_SUCCESS;
	pid = fork();
	if (pid == -1)
		return (ft_goprompt("fork", PRINT_ERROR));
	if (pid == 0)
		if (!ft_heredoc_op2(v))
			ft_exitbackprocss(v, EXIT_FAILURE);
	ft_fclose(&v->outfd);
	ft_fclose(&v->p1[1]);
	ft_fclose(&v->hdoc_fd);
	v->hdoc_fd = dup(v->p1[0]);
	ft_fclose(&v->p1[0]);
	if (v->hdoc_fd < 0)
		return (ft_goprompt("dup", __PERROR));
	if (!ft_pwait(v, pid, WNOHANG))
		return (__FALSE);
	return (__TRUE);
}

t_bool	ft_heredoc_op1(t_vars *v)
{
	char	*line;

	line = NULL;
	line = readline("> ");
	while (ft_strncmp(line, v->limiter, ft_strlen(v->limiter) + 1))
	{
		ft_putendl_fd(line, v->outfd);
		ft_freestr(&line);
		line = readline("> ");
	}
	ft_freestr(&line);
	ft_fclose(&v->outfd);
	ft_exitbackprocss(v, EXIT_SUCCESS);
	return (__FALSE);
}

char	*first_join(char *line, char *expand_content, size_t start_index)
{
	char	*ret;
	char	*cpy;

	ret = ft_substr(line, 0, start_index);
	if (!ret)
	{
		perror("minishell: expand_word_inside_line: ");
		return (NULL);
	}
	if (!expand_content)
		return (ret);
	cpy = ret;
	ret = ft_strjoin(ret, expand_content);
	free(cpy);
	if (!ret)
		perror("minishell: expand_word_inside_line: ");
	return (ret);
}

char	*second_join(char *line, char *ret, size_t end_index)
{
	char	*sub;
	char	*cpy;

	if (!ret)
	{
		free(line);
		return (NULL);
	}
	sub = ft_substr(line, end_index, ft_strlen(line));
	free(line);
	if (!sub)
	{
		perror("minishell: expand_word_inside_line: ");
		return (NULL);
	}
	cpy = ret;
	ret = ft_strjoin(ret, sub);
	if (!ret)
		perror("minishell: expand_word_inside_line: ");
	free(cpy);
	free(sub);
	return (ret);
}

char	*expand_exit_status_hdoc(char *line, size_t *start_index)
{
	char	*expand_number;
	char	*ret;

	expand_number = ft_itoa(exitstatus);
	if (!expand_number)
	{
		perror("minishell: expand_word_inside_line: ");
		return (NULL);
	}
	ret = first_join(line, expand_number, *start_index);
	ret = second_join(line, ret, *start_index + 2);
	free(expand_number);
	return (ret);
}

char	*expand_word_inside_line(t_vars *v, char *line, size_t *start_index)
{
	char	*expand_name;
	char	*expand_content;
	char	*ret;
	size_t	j;

	if (line[*start_index + 1] <= '9' && line[*start_index + 1] >= '0')
		return (line);
	j = 0;
	while (ft_isalnum(line[*start_index + 1 + j]))
		j++;
	expand_name = ft_substr(line, *start_index + 1, j);
	if (!expand_name)
	{
		free(line);
		perror("minishell: expand_word_inside_line: ");
		return (NULL);
	}
	expand_content = check_env_var_set(v, expand_name);
	ret = first_join(line, expand_content, *start_index);
	ret = second_join(line, ret, *start_index + 1 + j);
	if (expand_content)
		*start_index += ft_strlen(expand_content);
	free(expand_content);
	return (ret);
}

char	*expand_words_of_line(t_vars *v, char *line)
{
	size_t	l_index;

	l_index = 0;
	while (line[l_index] != '\0')
	{
		if (line[l_index] == '$' \
				&& expand_conditions(line[l_index + 1], __FALSE))
		{
			if (line[l_index + 1] == '?')
				line = expand_exit_status_hdoc(line, &l_index);
			else
				line = expand_word_inside_line(v, line, &l_index);
		}
		//what do we do if malloc error here
		else
			l_index++;
	}
	return (line);
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
		ft_exitbackprocss(v, !ft_goprompt(v->ftemp1, __PERROR));
	line = get_next_line(v->infd);
	while (line)
	{
		if (v->flg_expand_in_hdoc)
			line = expand_words_of_line(v, line);
		if (write(v->p1[1], line, ft_strlen(line)) < 0)
		{
			ft_freestr(&line);
			ft_exitbackprocss(v, EXIT_SUCCESS);
		}
		ft_freestr(&line);
		line = get_next_line(v->infd);
	}
	ft_freestr(&line);
	ft_exitbackprocss(v, EXIT_SUCCESS);
	return (__FALSE);
}
