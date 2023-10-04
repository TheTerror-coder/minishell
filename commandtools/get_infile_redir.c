/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmohin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:47:10 by lmohin            #+#    #+#             */
/*   Updated: 2023/10/04 23:59:20 by lmohin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_operator_after_infile_redir(char next_char);

char	*get_infile_redir(char *line, size_t *l_index)
{
	size_t	j;
	char	*infile_redir;

	if (check_operator_after_infile_redir(line[*l_index + 1]))
		return (NULL);
	j = 1;
	while (line[*l_index + j] != '\0' && is_whitespace(line[*l_index + j]))
		j++;
	if (line[*l_index + j] == '\0' || line[*l_index + j] == '|' \
		|| line[*l_index + j] == '<' || line[*l_index + j] == '>')
	{
		printf("minishell: syntax error: missing infile after \"<\"\n");
		return (NULL);
	}
	(*l_index) += 1;
	infile_redir = ft_strdup("<");
	if (!infile_redir)
		perror("minishell: get_infile_redir: ");
	return (infile_redir);
}

int	check_operator_after_infile_redir(char next_char)
{
	if (next_char == '>')
	{
		printf("minishell: syntax error: <> detected\n");
		return (1);
	}
	if (next_char == '|')
	{
		printf("minishell: syntax error: <| detected\n");
		return (1);
	}
	return (0);
}
