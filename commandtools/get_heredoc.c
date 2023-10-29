/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TheTerror <jfaye@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:47:10 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/29 20:36:08 by TheTerror        ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator_after_heredoc(t_vars *v, char next_char);

char	*get_heredoc(t_vars *v, char *line, size_t *l_index)
{
	size_t	j;
	char	*heredoc;

	if (check_operator_after_heredoc(v, line[*l_index + 2]))
	{
		v->exitstatus = 2;
		return (NULL);
	}
	j = 2;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0' || line[*l_index + j] == '|' \
		|| line[*l_index + j] == '<' || line[*l_index + j] == '>')
	{
		ft_putstr_fd("minishell: syntax error: missing delimitator for heredoc\n", 2);
		v->exitstatus = 2;
		return (NULL);
	}
	(*l_index) += 2;
	heredoc = ft_strdup("<<");
	if (!heredoc)
	{
		v->exitstatus = 1;
		perror("minishell: get_heredoc: ");
	}
	return (heredoc);
}

int	check_operator_after_heredoc(t_vars *v, char next_char)
{
	if (next_char == '<')
	{
		ft_putstr_fd("minishell: syntax error: <<< detected\n", 2);
		v->exitstatus = 2;
		return (1);
	}
	if (next_char == '>')
	{
		ft_putstr_fd("minishell: syntax error: <<> detected\n", 2);
		v->exitstatus = 2;
		return (1);
	}
	if (next_char == '|')
	{
		ft_putstr_fd("minishell: syntax error: <<| detected\n", 2);
		v->exitstatus = 2;
		return (1);
	}
	return (0);
}
