/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:47:10 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/26 23:38:57 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator_after_heredoc(char next_char);

char	*get_heredoc(char *line, size_t *l_index)
{
	size_t	j;
	char	*heredoc;

	if (check_operator_after_heredoc(line[*l_index + 2]))
	{
		exitstatus = 2;
		return (NULL);
	}
	j = 2;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0' || line[*l_index + j] == '|' \
		|| line[*l_index + j] == '<' || line[*l_index + j] == '>')
	{
		printf("minishell: syntax error: missing delimitator for heredoc\n");
		exitstatus = 2;
		return (NULL);
	}
	(*l_index) += 2;
	heredoc = ft_strdup("<<");
	if (!heredoc)
	{
		exitstatus = 1;
		perror("minishell: get_heredoc: ");
	}
	return (heredoc);
}

int	check_operator_after_heredoc(char next_char)
{
	if (next_char == '<')
	{
		printf("minishell: syntax error: <<< detected\n");
		exitstatus = 2;
		return (1);
	}
	if (next_char == '>')
	{
		printf("minishell: syntax error: <<> detected\n");
		exitstatus = 2;
		return (1);
	}
	if (next_char == '|')
	{
		printf("minishell: syntax error: <<| detected\n");
		exitstatus = 2;
		return (1);
	}
	return (0);
}
